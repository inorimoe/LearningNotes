关于C++模板的笔记

- [函数模板](#函数模板)
  - [1. 定义模板](#1-定义模板)
  - [2. 两阶段编译检查](#2-两阶段编译检查)
  - [3. 模板参数推断](#3-模板参数推断)
    - [类型推断中的类型转换](#类型推断中的类型转换)
    - [对默认调用参数的类型推断](#对默认调用参数的类型推断)
  - [4. 多个模板参数](#4-多个模板参数)
  - [5. 模板的返回类型](#5-模板的返回类型)
    - [作为返回类型的模板参数](#作为返回类型的模板参数)
    - [返回类型推断(C++11\\C++14)](#返回类型推断c11c14)
    - [将返回类型声明为公共类型(C++11)](#将返回类型声明为公共类型c11)
  - [6. 默认模板参数](#6-默认模板参数)
  - [7. 函数模板的重载](#7-函数模板的重载)
  - [8. 总结](#8-总结)
- [类模板](#类模板)
  - [类模板的实现](#类模板的实现)
    - [声明类模板](#声明类模板)
    - [成员函数的实现](#成员函数的实现)
  - [类模板的使用](#类模板的使用)
  - [部分使用类模板](#部分使用类模板)
  - [浅析友元](#浅析友元)
  - [类模板特化(全特化)](#类模板特化全特化)
  - [类模板偏特化](#类模板偏特化)
    - [多模板参数的部分特例化](#多模板参数的部分特例化)
  - [类模板的默认参数](#类模板的默认参数)
  - [类型别名](#类型别名)
    - [类型定义和别名声明](#类型定义和别名声明)
    - [模板别名](#模板别名)
    - [类成员的模板别名](#类成员的模板别名)
    - [Suffix\_t 类型萃取](#suffix_t-类型萃取)

---

# 函数模板

---

## 1. 定义模板

`template< 由逗号分割的模板参数>`
模板参数是 typename T;
关键字 typename 标识了一个类型参数 T. 类型参数可以任意标识，习惯上用 T;

```c++
template< typename T >
```

----

## 2. 两阶段编译检查

在定义没有报错误提示，模板是被分两步编译:
1.在模板定义阶段，模板的检查并不包含类型参数的检查。只包含下面几个方面:
>
> - 语法检查
> - 使用了未定义的不依赖于模板参数的名称(类型名，函数名)
> - 未使用模板参数的 static assertions

2.在模板实例化阶段, 模板会再次被检查;

-----

## 3. 模板参数推断

### 类型推断中的类型转换

在类型推断的时候自动的类型转换是受限制的:

1. 如果调用参数**引用传递**的，任何类型转换都不被允许。通过模板类型参数 T 定义的两个参数，它们实参的类型必须完全一样。

*类型转换引用传递.hpp*  
```C++ 
template<typename T>
T testRef(T& a, T const& b) {  return a;};

template<typename T>
T left(T& a) { return a; };

template<typename T>
T right(T const& b) {return b;};

template<typename T>
T testNoRef(T a, T const b) {
    return a;
};
int main(void) {
    const int i = 3;
    int j = 4;
    int k = 5;

    testRef(j, k); // OK,推断成int testRef<int>(int&, const int&);
    testRef(i, j); // ERROR, 推断成testRef<const int, int>(const int&, int&), T类型冲突;
    
    left(i);//OK, const int left<const int>(const int &);
    right(j);//OK, int right<int>(const int& b);
    const int tt = 3;
    right(tt);//int right<int>(const int& b);T被推导为int，可能是调用参数的类型不能转换；

    testNoRef(j, k);//OK, decay成int testNoRef<int>(int a,int b);
    testNoRef(i, j);//OK, decay成int testNoRef<int>(int a,int b);
    return 0;
}
```

2. 如果调用参数是**按值传递**的，那么只有退化（decay）这一类简单转换是被允许的：

>- const 和 volatile 限制符会被忽略.
>- 引用被转换成被引用的类型.
>- raw array 和函数被转换为相应的指针类型.

通过模板类型参数 T 定义的两个参数，它们实参的类型在退化（decay）后必须一样。

```C++
template<typename T>
T max (T a, T b);
…
int const c = 42;
int i = 1; 
int& ir = i;
int arr[4];
max(i, c); // OK: T 被推断为 int，c 中的 const 被 decay 掉;
max(i, ir); // OK: T 被推断为 int， ir 中的引用被 decay 掉
foo(&i, arr); // OK: T 被推断为 int*
```

3. 有多种办法解决推断错误  
   1. 对参数做类型转换.
        >max(4, 7.2); // ERROR: 不确定 T 该被推断为 int 还是 double
        >max(static_cast<double>(4), 7.2); // OK
   2. 显式地指出类型参数 T 的类型，这样编译器就不再会去做类型推导.
        >max<double>(4, 7.2); // OK
   3. 指明调用参数可能有不同的类型,利用[多个模板参数](#多个模板参数)

### 对默认调用参数的类型推断

需要注意的是，类型推断并不适用于默认调用参数

```C++
template<typename T>
void f(T = "");
...
f(1); // OK: T 被推断为 int, 调用 f<int> (1)
f(); // ERROR: 无法推断 T 的类型
```

为应对这一情况，你需要给模板类型参数也声明一个默认参数：

```C++
template<typename T = std::string>
void f(T = "");
...
f(); // OK
```

---

## 4. 多个模板参数

模板参数，定义在函数模板前面的尖括号里:

``` c++
template<typename T> // T 是模板参数 
```

调用参数，定义在函数模板名称后面的圆括号里:

``` c++
T max (T a, T b) // a 和 b 是调用参数
```

模板参数可以是一个或者多个.比如max()模板接受两个不同类型的调用参数：

```c++
template<typename T1, typename T2>
T1 max (T1 a, T2 b) {return b<a?a:b;>};
...
auto m = ::max(4, 7.2); // OK, 但是返回类型是第一个模板参数 T1 的类型
```

---

## 5. 模板的返回类型

C++提供了多种应对这一问题的方法：

1. [引入额外的模板参数作为返回类型](#作为返回类型的模板参数)
2. [让编译器找出返回类型]( #返回类型推断(C++11\C++14) )
3. [将返回类型定义为参数类型的“公共类型”](#将返回类型声明为公共类型(C++11))

### 作为返回类型的模板参数

1. 显式的指出模板参数的类型：

```c++
template<typename T>
T max (T a, T b);
...
::max<double>(4, 7.2); // max()被针对 double 实例化
```

2. 当模板参数和调用参数之间没有必然的联系,且模板参数不能确定的时候,模板类型推断又不会考虑返回类型,只能必须显式的指明模板参数的类型.如下:

```C++
template<typename T1, typename T2, typename RT>
RT max (T1 a, T2 b);
...
::max<int,double,double>(4, 7.2); // OK, 但是太繁琐
```

3. 另一种办法是只指定第一个模板参数的类型，其余参数的类型通过推断获得.
通常而言，我们必须显式指定所有模板参数的类型，直到某一个模板参数的类型可以被推断出来为止.因此，可以改变模板参数顺序，调用时只需要指定返回值的类型.

```c++
template<typename RT, typename T1, typename T2>
RT max (T1 a, T2 b);
...
::max<double>(4, 7.2) //OK: 返回类型是 double，T1 和 T2 根据调用参数推断
```

### 返回类型推断(C++11\C++14)

1. **C++14**返回类型不需要声明为任何模板参数类型,需要声明返回类型为`auto`;
必须要有推断返回类型的返回语句，而且多个返回语句之间的推断结果必须一致。

```C++
template<typename T1, typename T2>
auto max (T1 a, T2 b){return  b < a ? a : b;};
```

2. **C++11**尾置返回类型, 允许使用函数的调用参数;

```C++
template<typename T1, typename T2>
auto max (T1 a, T2 b) -> decltype(b<a?a:b)
{return b < a ? a : b;}
```

有个严重的问题：由于 T 可能是引用类型，返回类型就也可能被推断为引用类型。
☕初始化 auto 变量的时候其类型总是退化之后的类型。当函数返回类型是 auto 的时候也需要保持一致;☕
因此应该返回的是 decay 后的 T;

```C++
#include <type_traits>
template<typename T1, typename T2>
auto max (T1 a, T2 b) -> typename std::decay<decltype(true? a:b)>::type
//类型萃取（type trait）std::decay<>，它返回其 type 成员作为目标类型。
//由于其 type 成员是一个类型，为了获取其结果，需要用关键字 typename 修饰这个表达式。
{return b < a ? a : b;}
...
int i = 42;
int const& ir = i; // ir 是 i 的引用
auto a = ir; // a 的类型是 it decay 之后的类型，也就是int
auto b = max(i,ir); //b 的类型也是int
```

### 将返回类型声明为公共类型(C++11)

`C++11`标准库提供了一种指定 “更一般类型” 的方式。
`std::common_type<>::type` 产生的类型是他的两个模板参数的公共类型。

``` C++
#include <type_traits>
template<typename T1, typename T2>
std::common_type_t<T1, T2> max (T1 a, T2 b){return b < a ? a : b;}
```

std::common_type 也是一个类型萃取（type trait）, 定义在<type_traits>中，它返回一个结构体，结构体的 type 成员被用作目标类型。

``` C++
typename std::common_type<T1,T2>::type //since C++11
std::common_type_t<T1,T2> // equivalent since C++14
// `C++14` 简化了“萃取”的用法，只要在后面加个_t，就可以省掉 typename 和::type
```

std::common_type<>的结果也是退化的.

---

## 6. 默认模板参数
>
> 模板参数指定默认值。

这些默认值被称为默认模板参数，并且可以用于任意类型的模板。它们甚至可以根据其前面的模板参数来决定自己的类型.  
举个例子，返回类型的方法和多模板参数一起使用，你可以为返回类型引入一个模板参数 RT，并将其默认类型声明为其它两个模板参数的公共类型，以下多种实现方法：

1. 调用参数需要在被声明之前使用，只能先使用它们的类型。(因为这个例子在声明调用参数a、b之前使用操作符 `?:` );

```C++
#include <type_traits>
template<typename T1, typename T2, typename RT =
std::decay_t<decltype(true ? T1() : T2())>> //std::decay_t<>确保返回值不是引用类型
RT max (T1 a, T2 b)
{return b < a ? a : b;}
```

2. 也可以利用类型萃取 std::common_type<>作为返回类型的默认值：

```C++
#include <type_traits>
template<typename T1, typename T2, typename RT =
std::common_type_t<T1,T2>>
RT max (T1 a, T2 b) // std::common_type<>也会做类型退化处理；
{return b < a ? a : b;}
...
auto a = ::max(4, 7.2); //使用 RT 的默认值作为返回类型
```

3. 将返回类型作为第一个模板参数;

```C++
auto b = ::max<double,int,long double>(7.2, 4);  // 显式的指出所有的模板参数的类型作为返回类型
---------------------------------------------------------------------------
template<typename RT = long, typename T1, typename T2>
RT max (T1 a, T2 b)
{return b < a ? a : b;}
...
int i; long l;
max(i, l);  // 返回值类型是 long (RT 的默认值);
max<int>(4, 42);  //返回 int，因为其被显式指定;
```

## 7. 函数模板的重载

模板也是可以重载的, 可以定义多个有相同函数名的函数，当实际调用的时候，由 C++编译器负责决定具体该调用哪一个函数。

``` C++
int max (int a, int b){   // maximum of two int values:
  return b < a ? a : b;
}
template<typename T>      // maximum of two values of any type:
T max (T a, T b){
  return b < a ? a : b;
}
int main()
{
  ::max(7, 42);           // calls the nontemplate for two ints
  ::max(7.0, 42.0);       // calls max<double> (by argument deduction)
  ::max('a', 'b');        // calls max<char> (by argument deduction)
  ::max<>(7, 42);         // calls max<int> (by argumentdeduction)
  ::max<double>(7, 42);   // calls max<double> (no argumentdeduction)
  ::max('a', 42.7);       // calls the nontemplate for two ints
}
```

1.  **一个非模板函数可以和一个与其同名的函数模板共存，并且这个同名的函数模板可以被实例化为与非模板函数具有相同类型的调用参数**。
    - 函数调用时**匹配度相同，模板解析过程将优先选择非模板函数**。
    - 若显式指定模板列表，则优先调用模板函数。

    ```C++
    ::max(7, 42);       // both int values match the nontemplate function perfectly
    ```

    如果模板可以实例化出一个更匹配的函数，那么就会选择这个模板;

    ```C++
    ::max(7.0, 42.0);   // calls the max<double> (by argument deduction)
    ::max('a', 'b');    // calls the max<char> (by argument deduction)
    ```

    显式指定一个空的模板列表。这表明它会被解析成一个模板调用, 其所有的模板参数会被通过调用参数推断出来;

    ```C++
    ::max<>(7, 42);     // calls max<int> (by argument deduction)
    ```

2. 由于**函数模板的模板参数推断时不允许自动类型转换，而非模板函数是允许的**.因此最后一个调用会选择非模板参函数;
 
    ```C++
    ::max('a', 42.7);     //only the nontemplate function allows nontrivial  conversions
    ```

3. 调用函数模板时，**必须保证函数模板已经在前面某处定义**。

    ```C++
    int max(int a, int b) {
        return a > b ? a : b;
    }
    template <typename T>
    T max(T a, T b, T c) {
        return max(max(a,b),c);  //T为int时，并不会调用max<int>,而是调用非模板函数max(int,int)
    }
    template <typename T>
    T max(T a, T b) {
        return a > b ? a : b;
    }
    ...
    max(1, 2, 3);  // 最终调用非模板函数max(int,int)比较
    max("sjx", "wyl", "shh"); //error,在前方找不到二元的模板函数max<const char *>的定义,
    ```

---

## 8. 总结

- 函数模板定义了一组适用于不同类型的函数。
- 当向模板函数传递变量时，函数模板会自行推断模板参数的类型，来决定去实例化出那种类型的函数。
- 你也可以显式的指出模板参数的类型。
- 你可以定义模板参数的默认值。这个默认值可以使用该模板参数前面的模板参数的类型，而且其后面的模板参数可以没有默认值。
- 函数模板可以被重载。
- 当定义新的函数模板来重载已有的函数模板时，必须要确保在任何调用情况下都只有一个模板是最匹配的。
- 当你重载函数模板的时候，最好只是显式地指出了模板参数得了类型。
- 确保在调用某个函数模板之前，编译器已经看到了相对应的模板定义。

---

# 类模板  

## 类模板的实现

以一个栈（stack）的例子来展示类模板的使用:

```C++
#include <vector>
#include <cassert>
template<typename T>
class Stack {
private:
    std::vector<T> elems; // elements
public:
    void push(T const& elem); // push element
    void pop(); // pop element
    T const& top() const; // return top element
    bool empty() const { // return whether the stack is empty
        return elems.empty();
    }
};
template<typename T>
void Stack<T>::push (T const& elem)
{
    elems.push_back(elem); // append copy of passed elem
}
template<typename T>
void Stack<T>::pop ()
{
    assert(!elems.empty());
    elems.pop_back(); // remove last element
}
template<typename T>
T const& Stack<T>::top () const
{
    assert(!elems.empty());
    return elems.back(); // return copy of last element
}
```

### 声明类模板  

1. 类模板不可以定义在函数作用域或者块作用域内部，通常定义在 global/namespace/类作用域。  

2. 在类模板中使用类名 (不带模板参数)，表明这个内部类的模板参数类型和模板类的参数类型相同 [(13.2.3注入类型)](#注入类型)。

   ```C++
    template<typename T>
    class Stack {
    ...
    Stack (Stack const&); // copy constructor
    Stack (Stack<T> const&); // copy constructor
    ---
    Stack& operator= (Stack const&); // assignment operators
    Stack<T>& operator= (Stack<T> const&); // assignment operator
    ...
    };
   ```

### 成员函数的实现  

- 参考[类模板的实现](#类模板的实现)

---

## 类模板的使用

1. c++17前，使用类模板都需要**显式**指定模板参数`type<T>`。 C++17有**类参数模板推导**。

2. **类模板的成员函数只有在调用的时候才会实例化。**
3. 如果一个类模板有 static 成员，对于使用类模板的每个类型实例，相应的静态成员也只会被实例化一次。

---

## 部分使用类模板

1. 类模板实例化时，模板参数只需要支持被实例化部分所有用到的操作。

    ```C++
    template<typename T>
    class Stack {
    ...
        void print(std::ostream& strm) const {
            for (T const& elem : elems) {
                strm << elem << ' '; // 对每个元素使用<<
            }
        }
    };
    int main()
    {
        // 只会实例化类模板中的push 和 print函数
        Stack<int> s;
        s.push(3);
        s.print(std::cout);

        // Stack<int>未重载<<运算符，实例化print函数时失败
        Stack<Stack<int>> ss;
        ss.push(s);
        ss.print(std::cout);
        return 0;
    }
    ```

2. c++11 开始，可以通过 static_assert 和 type_traits 做一些简单的类型检查

    ```C++
    template <typename T>
    class C
    {
        static_assert(std::is_default_constructible<T>::value,
        "class C requires default contructible");
    };
    ```  

---  

## 浅析友元  
浅析友元，深入了解见[（第二部分深入了解模板）12.5 友元](#12.5友元)  

```C++
template<typename T>
class Stack {
…
    //一般打印函数的两种实现思路
    void print() (std::ostream& strm) const {…}
    friend std::ostream& operator<< (std::ostream& strm, Stack<T> const& s) {
        /* operator<<并不是一个函数模板（对于在模板类内定义这一情况），
           而是在需要的时候，随类模板实例化出来的一个常规函数. */
        s.print(strm);
        return strm;
    }
};
```

先声明一个友元函数，然后再去定义它，事实上有两种选择：

1. 隐式的声明一个新的函数模板，但是必须使用一个不同的模板参数，比如 U。

    ```C++
    template<typename T>
    class Stack {
        …
        template<typename U>
        friend std::ostream& operator<< (std::ostream&, Stack<U> const&);
    };
    ```

    无论是继续使用 T 还是省略掉模板参数声明，都不可以（要么是里面的 T 隐藏了外面的 T，要么是在命名空间作用域内声明了一个非模板函数）。  

2. 使用前向声明（Forward Declaration）。先将Stack< T >的operator<<声明为一个模板，这要求先对 Stack < T > 进行声明:  
   
    ```c++
    template<typename T>
    class Stack;
    template<typename T>
    std::ostream& operator<< (std::ostream&, Stack<T> const&);
    ...
    template<typename T>
    class Stack {
        ...
        friend std::ostream& operator<< <T> (std::ostream&, Stack<T> const&);
    }       
    ``` 

    注意函数名operator<<后面的`<T>`。 因此，我们将非成员函数模板的特化声明为 friend，如果没有 <T>，我们将声明一个新的非模板函数。详见[（第二部分深入了解模板）12.5.2 函数友元](#12.5.2函数友元)

---

## 类模板特化(全特化)

要对类模板进行特化，必须在类声明中以 **template<>** 为前导，并**指定类模板要特化的类型**。这些类型**作为模板参数使用**，必须在类名之后直接指定：

```C++
template<>
class Stack<std::string> { //Stack<T>类模板的特化
    ...
}
```

对类模板进行特化可以优化某些类型的实现，或者避免某些类型在类模板实例化中的错误行为。

- 如果要对一个类模板进行专门化，则必须特化所有成员函数。
- 可以对类模板中的单个成员函数进行特化，但是就不能再对特化成员所属的整个类模板实例进行特化。

对于这些特化，成员函数的任何定义都必须定义为 "普通 "成员函数，T 的每一次出现都由特化类型代替：

```C++
void Stack<std::string>::push (std::string const& elem){
    elems.push_back(elem); // append copy of passed elem
}
```
下面是 std::string 类型的 Stack<> 特化的完整示例, 它的一些成员函数做了优化:
```C++
#include "stack1.hpp"
#include <deque>
#include <string>
#include <cassert>
template<>
class Stack<std::string> {
private:
    std::deque<std::string> elems;  // elements
public:
    void push(std::string const&);  // push element
    void pop();// pop element
    std::string const& top() const; // return top element
    bool empty() const {            // return whether the stack is empty
        return elems.empty();
    }
};
void Stack<std::string>::push (std::string const& elem){
    elems.push_back(elem);  // append copy of passed elem
}
void Stack<std::string>::pop (){
    assert(!elems.empty());
    elems.pop_back(); // remove last element
}
std::string const& Stack<std::string>::top () const {
    assert(!elems.empty());
    return elems.back(); // return copy of last element
}
```

---

## 类模板偏特化

> 类模板特化时，可以**只特化部分参数**（或者说对参数进行部分特化）。

例如，我们可以为指针我们定义了一个类模板，仍然为T参数化，但特化用来处理指针的类模板（Stack＜T*＞）。

```C++
template<typename T>
class Stack<T*> { };
```

以下是该Stack模板类的T*偏特化实现：

```C++
#include "stack.hpp"
// partial specialization of class Stack<> for pointers:
template<typename T>
class Stack<T*> {
private:
    std::vector<T*> elems; // elements
public:
    void push(T*); // push element
    T* pop(); // pop element
    T* top() const; // return top element
    bool empty() const { // return whether the stack is empty
        return elems.empty();
    }
};

template<typename T>
void Stack<T*>::push (T* elem)
{
    elems.push_back(elem); // append copy of passed elem
}

template<typename T>
T* Stack<T*>::pop ()
{
    assert(!elems.empty());
    T* p = elems.back();
    elems.pop_back(); // remove last element
    return p; // and return it (unlike in the general case)
}

template<typename T>
T* Stack<T*>::top () const
{
    assert(!elems.empty());
    return elems.back(); // return copy of last element
}
```

注意，特化之后的函数接口可能不同。例如，返回 T 类型可以自动回收内存（RAII），而特化为 T* 可能需要手动回收内存。

### 多模板参数的部分特例化  

类模板还可以将多个模板参数部分特化，例如下面的类模板：

```C++
template<typename T1, typename T2>
class MyClass {
...
};
// partial specialization: both template parameters have same type
template<typename T>
class MyClass<T, T> {
...
};
// partial specialization: second type is int
template<typename T>
class MyClass<T, int> {
...
};
// partial specialization: both template parameters are pointer types
template<typename T1, typename T2>
class MyClass<T1*, T2*> {
...
};

MyClass<int, float> mif;     // uses MyClass<T1,T2>
MyClass<float, float> mff;   // uses MyClass<T,T>
MyClass<float, int> mfi;     // uses MyClass<T,int>
MyClass<int*, float*> mp;    // uses MyClass<T1*,T2*>
```

若多个偏特化都匹配调用，则声明有歧义。要解决歧义，可以为相同类型的指针提供偏特化实现:

```C++
template<typename T>
class MyClass<T*, T*> {
…
};
```
---
## 类模板的默认参数  

对于函数模板，可以为类模板参数设置默认值。
***声明定义:***
```C++
#include <vector>
#include <cassert>
template<typename T, typename Cont = std::vector<T>>
class Stack {
private:
    Cont elems; // elements
public:
    void push(T const& elem); // push element
    void pop(); // pop element
    T const& top() const; // return top element
    bool empty() const { // return whether the stack is
        emptyreturn elems.empty();
    }
};
//现在有两个模板参数，因此下面每个成员函数的定义也应该包含两个模板参数：
template<typename T, typename Cont>
void Stack<T,Cont>::push (T const& elem)
{
    elems.push_back(elem); // append copy of passed elem
}
template<typename T, typename Cont>
void Stack<T,Cont>::pop ()
{
    assert(!elems.empty());
    elems.pop_back(); // remove last element
}
template<typename T, typename Cont>
T const& Stack<T,Cont>::top () const
{
    assert(!elems.empty());
    return elems.back(); // return copy of last element
}
```

***使用:***
```C++
#include "stack3.hpp"
#include <iostream>
#include <deque>
int main()
{
    // stack of ints:
    Stack<int> intStack;

    // stack of doubles using a std::deque<> to manage the elements
    Stack<double,std::deque<double>> dblStack;

    // manipulate int stack
    intStack.push(7);
    std::cout << intStack.top() << '\n';
    intStack.pop();

    // manipulate double stack
    dblStack.push(42.42);
    std::cout << dblStack.top() << '\n';
    dblStack.pop();
}
```

## 类型别名

### 类型定义和别名声明

在这两种情况下我们都只是为一个已经存在的类型定义了一个别名，并没有定义新的类型， 两者等价。

1. 通过使用关键字 **typedef**.
2. 通过使用关键字 **using**(C++11 起).

```C++
typedef Stack<int> IntStack; // typedef
void foo (IntStack const& s); // s is stack of ints
IntStack istack[10]; // istack is array of 10 stacks of ints

using IntStack = Stack <int>; // alias declaration
void foo (IntStack const& s); // s is stack of ints
IntStack istack[10]; // istack is array of 10 stacks of ints
```

### 模板别名  
不同于 typedef， **别名声明 using**也可以被模板化，这样就可以给一组类型取一个方便的名字。
```C++
template<typename T>
using DequeStack = Stack<T, std::deque<T>>;
...
//
static_assert(std::is_same_v<DequeStack<int>, Stack<int, std::deque<int>>> == true);
```
模板只能在**全局global / 命名空间namespace**作用域或类声明内部声明和定义.

### 类成员的模板别名  

### Suffix_t 类型萃取

