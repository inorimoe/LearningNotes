

- [什么是协程](#什么是协程)
- [co\_await](#co_await)
- [awaitable 和 awaiter 的解释](#awaitable-和-awaiter-的解释)
- [coroutine\_handle](#coroutine_handle)
- [coroutine body 协程体的简略执行逻辑](#coroutine-body-协程体的简略执行逻辑)
- [co\_yield](#co_yield)
- [coroutine state 协程状态](#coroutine-state-协程状态)
- [promise\_type](#promise_type)
    - [协程函数返回值 returned\_type 类型定义](#协程函数返回值-returned_type-类型定义)
    - [coroutine\_traits的协程特化](#coroutine_traits的协程特化)
- [图解协程代码运行逻辑](#图解协程代码运行逻辑)
- [有栈协程与无栈协程的区别](#有栈协程与无栈协程的区别)
- [reference 参考资料](#reference-参考资料)

## 什么是协程
协程相关的关键字，有下面三个：
* co_await
* co_yield
* co_return  

一个协程里只能使用 co_return，不能使用 return。
<b>这三个关键字只要有一个出现在函数中，这个函数就是一个协程</b>——从外部则看不出来，没有用其他语言常用的 async 关键字来标记（async 已经有其他用途,见***std::async*** ）。
C++ 认为一个函数是否是一个协程是一个实现细节，不是对外接口的一部分。

实际上C++ 的编译器如何识别协程函数呢？是通过**函数返回值类型**。
C++ 协程函数的返回值类型有要求:
* `协程状态` (coroutine state):记录协程状态，是分配于堆的内部对象：
  ```
  * 形参（协程函数的参数）
  * 协程挂起的点
  * 临时变量
  ```
* `承诺对象`（promise）: 从协程内部操纵。协程通过 promise_type 对象提交其结果或异常。
* `协程句柄`（coroutine_handle）: 协程的唯一标示。用于恢复协程执行或销毁协程帧。

C++ 协程函通过自定义等待体 Awaitable 来控制如何执行挂起的调度。
* `Awaitable` or `Awaiter`: co_await 关键字调用的对象。

## co_await

一般co_await的使用如下。
```c++
auto result = co_await 表达式; //暂停执行直到恢复
```
对于这里的**表达式**(expression)，编译器会把它理解为：
```c++
auto&& __a = 表达式;
if (!__a.await_ready()) {
  __a.await_suspend(std::coroutine_handle<>...); //参数是协程句柄
  // 挂起/恢复点
}
auto result = __a.await_resume();
```
"表达式" 需要支持 `await_ready`、`await_suspend` 和 `await_resume` 三个接口。

如果 await_ready() 返回True，就代表不需要真正挂起，直接返回后面的结果就可以；（Q：是否执行await_resume()后，返回结果？）
否则 await_ready() 返回False，返回执行 await_suspend 之后即挂起协程，等待协程被唤醒之后再返回 await_resume() 的结果。
这样的一个表达式被称作是个[awaitable]( #awaitable-和-awaiter-的解释)。

标准里定义了两个 awaitable，如下所示：
```c++
struct suspend_always {
  bool await_ready() const noexcept
  {
    return false;
  }
  void await_suspend( coroutine_handle<> ) const noexcept {}
  void await_resume() const noexcept {}
};

struct suspend_never {
  bool await_ready() const noexcept
  {
    return true;
  }
  void await_suspend(coroutine_handle<>) const  noexcept {}
  void await_resume()
    const noexcept {}
};
```
`suspend_always` 永远告诉调用者需要挂起;
`suspend_never` 则永远告诉调用者不需要挂起。
两者的 await_suspend 和 await_resume 都是平凡实现，不做任何实际的事情。
一个 awaitable 可以*自行实现这些接口*`await_ready`、`await_suspend` 和 `await_resume`，以定制对应的**挂起之前、如何挂起、恢复之后**需要执行的操作.

## awaitable 和 awaiter 的解释

[cppreference的awaitable&&awaiter介绍，在co_await讲解里面。](https://en.cppreference.com/w/cpp/language/coroutines)
ps:直接看英文，译文会丢失信息。
![awaitable&&awaiter](./CoroutinesImages/awaitable&&awaiter.png)

<p style="color:red">[?]这一段感觉很怪，有可能理解 awaitable 和 awaiter 出现偏差，需要实现awaitable 和 awaiter 结构体代码检验。</p>

首先，以下列方式将`co_await expr`的 expr（表达式） 视为 awaitable（可等待体）：
* 如果 表达式 由初始暂停点、最终暂停点或 yield 表达式所产生，那么awaitable是 表达式 本身。
* 否则，如果当前协程的承诺类型 Promise 拥有成员函数 await_transform，那么 awaitable 是 promise.await_transform(表达式)。
* 否则，awaitable是 表达式 本身。

然后以下列方式获得 awaiter（等待器）对象：
* 如果针对 operator co_await 的重载决议给出单个最佳重载，那么 awaiter 是该调用的结果:
  * 对于成员重载为 `awaitable.operator co_await();`
  * 对于非成员重载为 `operator co_await(static_cast<Awaitable&&>(awaitable));`
* 否则，<b> 如果重载决议找不到 operator co_await，那么 awaiter 是 awaitable 本身 </b>。
* 否则，如果重载决议有歧义，那么程序非良构。

## coroutine_handle
coroutine_handle 是 C++ 标准库提供的类模板。这个类是用户代码跟系统协程调度真正交互的地方，有下面这些成员函数会用到：
1. destroy：销毁协程;
2. done：判断协程是否已经执行完成;
3. resume：让协程恢复执行;
4. promise_type：通过**实现**在协程**执行期间**的**特定点调用的方法**来**定义和控制**协程本身的行为。
   1. 在某些用例中，协程 Promise 对象确实起着与 std::future 对的 std::promise 部分类似的作用，但对于其他用例，这种类比有些不适用。
   2. 将协程的 Promise 对象视为"**协程状态控制器**"对象可能更容易，该对象控制协程的行为并可用于跟踪其状态。
5. from_promise（静态）：通过 promise_type 对象的引用来生成一个协程句柄;

## coroutine body 协程体的简略执行逻辑

协程的执行过程大致是这个样子的：
1. 为协程调用分配一个协程帧，含协程调用的参数、变量、状态、promise 对象等所需的空间。
2. 调用 promise.get_return_object()，返回值会在协程第一次挂起时返回给协程的调用者。
3. 执行 co_await promise.initial_suspsend()；根据上面对 co_await 语义的描述，协程可能在此第一次挂起（但也可能此时不挂起，在后面的协程体执行过程中挂起）。
4. 执行协程体中的语句，中间可能有挂起和恢复；如果期间发生异常没有在协程体中处理，则调用 promise.unhandled_exception()。
5. 当协程执行到底，或者执行到 co_return 语句时，会根据是否有非 void 的返回值，调用 promise.return_value(…) 或 promise.return_void()，然后执行 co_await promise.final_suspsend()。

*伪代码逻辑*
```c++

  frame = operator new(…);
  promise_type& promise = frame->promise;

  // 在初次挂起时返回给调用者
  auto return_value = promise.get_return_object();

  co_await promise.initial_suspsend();
  try {
    执行自定义协程体 coroutine body;
    可能被 co_wait、co_yield 挂起;
    恢复后继续执行，直到 co_return;
  }
  catch (...) {
    promise.unhandled_exception();
  }

  final_suspend:
    co_await promise.final_suspsend();
```

## co_yield
`co_yield`的表达式等价于：
```C++
co_await promise.yield_value(表达式);
```

## coroutine state 协程状态
见[cppreference::coroutines::Execution](https://en.cppreference.com/w/cpp/language/coroutines)
![coroutine_state](./CoroutinesImages/coroutine_state.png)
协程状态 (coroutine state)，它是一个动态存储分配（除非优化掉其分配）的内部对象，其包含：
* 承诺对象
* 各个形参（全部按值复制）
* 当前暂停点的一些表示，使得程序在恢复时知晓要从何处继续，销毁时知晓有哪些局部变量在作用域内
* 生存期跨过当前暂停点的局部变量和临时量

当协程开始执行时，它进行下列操作：
* 用 operator new 分配协程状态对象
* 将所有函数形参复制到协程状态中：按值传递的形参被移动或复制，按引用传递的参数保持为引用（因此，如果在被指代对象的生存期结束后恢复协程，它可能变成悬垂引用）

## promise_type
promise_type被编译器用来控制协程的行为。有两种使用方式：应该将其定义为协程类型的成员
```
promise_type
  |-> returned_type::promise_type // 定义为协程类型的成员
  |-> std::coroutine_traits       // 定义为coroutine_traits模板特化类型的公开成员
      |-> std::coroutine_traits<R, Args...>::promise_type
```
#### 协程函数返回值 returned_type 类型定义
```C++
class Task
{
public:
    using co_handle = coroutine_handle<promise_type>;
    struct promise_type {
        // creating coroutine object -mandatory强制
        auto get_return_object() { return Task{std::
            coroutine_handle<promise_type>::from_promise(*this)}; }
        
        // returns awaitable object - mandatory强制
        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() { return std::suspend_always{}; }

        // one of below is mandatory强制 and only one must be present在场的;
        auto return_value(int val) { value_ = val; return std::suspend_never{};}
        void return_void() {}
        
        // mandatory强制
        void unhandled_exception() { std::terminate(); }

        // support for yielding values - returns awaitable;
        // co_yield 表达式，返回 awaitable； 
        auto yield_value(uint64_t value){ value_ = value; return suspend_always(); }

        // modification of the awaitable;
        auto await_transform(/*co_await operand*/ );
        
        uint64_t value_;
    };
    explicit Task(co_handle handle) : handle_(handle) { }
    ~Task(){ handle_.destroy(); }
    Task(const Task&) = delete;
    Task(Task&&) = default;
public:
//自定义函数
    bool resume(){ if(!handle_.done()){ handle_.resume(); } return !handle_.done();}
    uint64_t get(){ return handle_.promise().value_; }
private:  
    co_handle handle_;
};
```
协程函数返回值`returned_type`类型，这里定义为 `Task`类。结构内部有个 `promise_type`，而私有成员只有一个协程`句柄handle`。
协程构造需要一个协程句柄，析构时将使用协程句柄来销毁协程；为简单起见，我们允许结构被移动，但不可复制（以免重复调用 `handle_.destroy()`）
自定义函数：`resume()` 会判断协程是否已经结束，没结束就恢复协程的执行；当协程再次挂起时（调用者恢复执行），返回协程是否仍在执行中的状态。而 `get()` 简单地返回存储在 `promise` 对象中的数值。
1. Promise 结构里面可以存放数据，比如数据成员 `value_`，存放供 Task::get 取用的数值。
2. `get_return_object()`
   调用协程的返回值就是 `get_return_object()` 的结果。这儿就是使用 promise 对象来构造一个类型Task。
3. `initial_suspend()`
   此处返回 suspend_always()，即协程立即挂起，调用者马上得到 get_return_object() 的结果。
4. `final_suspend()`
   此处返回 suspend_always()，即使执行到了 co_return 语句，协程仍处于挂起状态。
   如果我们返回 suspend_never() 的话，那一旦执行了 co_return 或执行到协程结束，协程就会被销毁，连同已初始化的本地变量和 promise，并释放协程帧内存。
5. `yield_value()`
   调用`co_yield`后会调用这个函数，可以保存co_yield的结果，其返回其返回值为std::suspend_always表示协程会挂起，如果返回std::suspend_never表示不挂起。这儿仅对 value_ 进行赋值，然后让协程挂起（执行控制回到调用者）。
6. `return_void()`
    调用`return_void()`有以下情况：
   1. co_return;
   2. co_return expr; 当expr是的类型是void
7. `return_value(expr)`
   `return_value()`函数用于获取协程的返回值。当协程执行完成时，可以使用 co_return 语句返回一个值，然后 return_value() 函数将获取这个返回值。这样的机制可以让我们在协程执行期间获取协程的返回值，而不必等到整个协程执行完毕。
   
8. `unhandled_exception()`
   我们这儿也不应该发生任何异常，所以我们简单地调用 terminate 来终结程序的执行。

9. `await_transform`
    `await_transform()`是协程内部用于处理 co_await 表达式的函数。当在协程中使用 co_await 时，编译器会调用 await_transform() 来转换 co_await 表达式的操作数。

#### coroutine_traits的协程特化
coroutine_traits 是 C++ 中协程相关的模板类，用于定义和定制协程的返回类型和 promise_type。通过特化 coroutine_traits 模板包括返回类型、promise_type 等, 来自定义协程的行为。
coroutine_traits：https://en.cppreference.com/w/cpp/coroutine/coroutine_traits


## 图解协程代码运行逻辑
结合下面代码进行修改
https://godbolt.org/z/f979oYznP
[待完善,参考图解协程的内容]
```C++
#include <coroutine>
#include <iostream>
struct CoroutineTask {
    struct promise_type {
        auto initial_suspend() { return std::suspend_never{}; }
        auto final_suspend() noexcept {
            std::cout << "final_suspend called" << std::endl;
            return std::suspend_always{};
        }
        CoroutineTask get_return_object() {
            return CoroutineTask{
                std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        void return_void() { std::cout << "co_return called" << std::endl; }
        void unhandled_exception() {}
        ~promise_type() {
            std::cout << "Promise Destructor called" << std::endl;
        }
    };
    std::coroutine_handle<promise_type> coro_handle;
    CoroutineTask(std::coroutine_handle<promise_type> h) : coro_handle(h) {}
    ~CoroutineTask() {
        // 如果final_suspend返回std::suspend_never, 会自动析构Promise;
        // 如果final_suspend返回std::suspend_always，则需下列这行destroy析构Promise以免泄露;
        // if (coro_handle) coro_handle.destroy();
        std::cout << "Destructor called" << std::endl;
    }
    void resume() {
        std::cout << "Call Coroutine resume" << std::endl;
        coro_handle.resume();
    }
};

CoroutineTask simpleCoroutine() {
    std::cout << "Coroutine started" << std::endl;
    co_await std::suspend_always{};
    std::cout << "Coroutine resumed"
              << std::endl;
    co_return;
}

int main() {
    auto coro = simpleCoroutine();
    std::cout << "Main function" << std::endl;
    coro.resume();
    std::cout << "Main function end" << std::endl;
    return 0;
}
--------------------------------------------------------
执行结果：
coroutine started
Main function
Call Coroutine resume
Coroutine resumed
co_return called
final_suspend called
Main function end
Destructor called
```
[?] 问题一：将std::suspend_never 与 std::suspend_always 互换看看有什么不同;
1. 如果全部换成std::suspend_never;
Promise先析构，Coroutine等生命周期结束再析构。[待完善,参考图解协程的内容]

## 有栈协程与无栈协程的区别
**有栈协程:**
有栈的协程跟纤程、goroutines 基本是一个概念，都是由用户自行调度的、操作系统之外的运行单元。每个这样的运行单元都有自己独立的栈空间，缺点当然就是栈的空间占用和切换栈的开销了。
**无栈协程:**
无栈的协程自己没有独立的栈空间，每个协程只需要一个很小的栈帧，空间占用小，也没有栈的切换开销。
C++20 的协程是无栈的。部分原因是有栈的协程可以使用纯库方式实现，而无栈的协程需要一点编译器魔法帮忙。毕竟，协程里面的变量都是要放到堆上而不是栈上的。
一个简单的无栈协程调用的内存布局如下图所示：
![Alt text](./CoroutinesImages/noStackCoroutines.png)

## reference 参考资料
|参考资料|
|-|
|[吴咏炜：现代 C++ 编程实战，“30 Coroutines:协作式的交叉调度执行”](https://time.geekbang.org/column/article/196785)|
|[Cppreference.com: Coroutines](https://en.cppreference.com/w/cpp/language/coroutines)|
|[一篇文章搞懂c++ 20 协程 Coroutine](https://zhuanlan.zhihu.com/p/615828280)|
|[coroutines-cheatsheet.pdf](https://github.com/dawidpilarski/coroutine-cheatsheet/blob/master/coroutines-cheatsheet.pdf)|
|[Asymmetric Transfer](https://lewissbaker.github.io)|
|[C++20 Coroutines — Complete* Guide](https://itnext.io/c-20-coroutines-complete-guide-7c3fc08db89d)|