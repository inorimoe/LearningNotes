|参考资料|
|-|
|[吴咏炜：现代 C++ 编程实战，“30 Coroutines:协作式的交叉调度执行”](https://time.geekbang.org/column/article/196785)|
|[Cppreference.com: Coroutines](https://en.cppreference.com/w/cpp/language/coroutines)|
|[一篇文章搞懂c++ 20 协程 Coroutine](https://zhuanlan.zhihu.com/p/615828280)|
### 什么是协程
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

### co_await

一般co_await的使用如下。
```c++
auto result = co_await 表达式; //暂停执行直到恢复
```
对于这里的**表达式**(expression)，编译器会把它理解为：
```c++
auto&& __a = 表达式;
if (!__a.await_ready()) {
  __a.await_suspend(协程句柄);
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
  void await_suspend(
    coroutine_handle<>)
    const noexcept {}
  void await_resume()
    const noexcept {}
};

struct suspend_never {
  bool await_ready() const noexcept
  {
    return true;
  }
  void await_suspend(
    coroutine_handle<>)
    const noexcept {}
  void await_resume()
    const noexcept {}
};
```
`suspend_always` 永远告诉调用者需要挂起;
`suspend_never` 则永远告诉调用者不需要挂起。
两者的 await_suspend 和 await_resume 都是平凡实现，不做任何实际的事情。
一个 awaitable 可以*自行实现这些接口*`await_ready`、`await_suspend` 和 `await_resume`，以定制对应的**挂起之前、如何挂起、恢复之后**需要执行的操作.

### awaitable 和 awaiter 的解释
[cppreference的awaitable&&awaiter介绍，在co_await讲解里面。](https://en.cppreference.com/w/cpp/language/coroutines)
ps:直接看英文，译文会丢失信息。
![awaitable&&awaiter](./CoroutinesImages/awaitable&&awaiter.png)
这里awaiter明显是重载决议获得，默认将`co_await expr`的expr视为await。[?]

### coroutine_handle
coroutine_handle 是 C++ 标准库提供的类模板。这个类是用户代码跟系统协程调度真正交互的地方
1. destroy：销毁协程;
2. done：判断协程是否已经执行完成;
3. resume：让协程恢复执行;
4. promise_type：通过**实现**在协程**执行期间**的**特定点调用的方法**来**定义和控制**协程本身的行为。
   1. 在某些用例中，协程 Promise 对象确实起着与 std::future 对的 std::promise 部分类似的作用，但对于其他用例，这种类比有些不适用。
   2. 将协程的 Promise 对象视为"**协程状态控制器**"对象可能更容易，该对象控制协程的行为并可用于跟踪其状态。
5. from_promise（静态）：通过 promise_type 对象的引用来生成一个协程句柄;

### 协程的执行过程
[待完善,参考图解协程的内容]
协程的执行过程大致是这个样子的：
1. 为协程调用分配一个协程帧，含协程调用的参数、变量、状态、promise 对象等所需的空间。
2. 调用 promise.get_return_object()，返回值会在协程第一次挂起时返回给协程的调用者。
3. 执行 co_await promise.initial_suspsend()；根据上面对 co_await 语义的描述，协程可能在此第一次挂起（但也可能此时不挂起，在后面的协程体执行过程中挂起）。
4. 执行协程体中的语句，中间可能有挂起和恢复；如果期间发生异常没有在协程体中处理，则调用 promise.unhandled_exception()。
5. 当协程执行到底，或者执行到 co_return 语句时，会根据是否有非 void 的返回值，调用 promise.return_value(…) 或 promise.return_void()，然后执行 co_await promise.final_suspsend()。

```c++
  frame = operator new(…);
  promise_type& promise =
    frame->promise;

  // 在初次挂起时返回给调用者
  auto return_value =
    promise.get_return_object();

  co_await promise
    .initial_suspsend();
  try {
    执行协程体;
    可能被 co_wait、co_yield 挂起;
    恢复后继续执行，直到 co_return;
  }
  catch (...) {
    promise.unhandled_exception();
  }

final_suspend:
  co_await promise.final_suspsend();
```

### co_yield
`co_yield`的表达式等价于：
```C++
co_await promise.yield_value(表达式);
```
---------------------------------------------
极客时间coroutines阅读至uint64_resumable，待完善。

