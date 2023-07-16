关于C++模板的笔记

- [函数模板](#函数模板)
  - [定义模板](#定义模板)
  - [两阶段编译检查](#两阶段编译检查)
  - [模板参数推断](#模板参数推断)
    - [类型推断中的类型转换](#类型推断中的类型转换)
    - [对默认调用参数的类型推断](#对默认调用参数的类型推断)
  - [多个模板参数](#多个模板参数)
  - [模板的返回类型](#模板的返回类型)
    - [作为返回类型的模板参数](#作为返回类型的模板参数)
    - [返回类型推断(C++11\\C++14)](#返回类型推断c11c14)
    - [将返回类型声明为公共类型(C++11)](#将返回类型声明为公共类型c11)
  - [默认模板参数](#默认模板参数)
  - [函数模板的重载](#函数模板的重载)

---

# 函数模板

---

## 定义模板

`template< 由逗号分割的模板参数>`
模板参数是 typename T;
关键字 typename 标识了一个类型参数 T. 类型参数可以任意标识，习惯上用 T;

```c++
template< typename T >
```

----

## 两阶段编译检查

在定义没有报错误提示，模板是被分两步编译:
1.在模板定义阶段，模板的检查并不包含类型参数的检查。只包含下面几个方面:
>
> - 语法检查
> - 使用了未定义的不依赖于模板参数的名称(类型名，函数名)
> - 未使用模板参数的 static assertions

2.在模板实例化阶段, 模板会再次被检查;

-----

## 模板参数推断

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

1. 如果调用参数是**按值传递**的，那么只有退化（decay）这一类简单转换是被允许的：

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

## 多个模板参数

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

## 模板的返回类型

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

## 默认模板参数
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

## 函数模板的重载

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
template<typename T>
T max (T a, T b){
  return b < a ? a : b;
}
```

1. **一个非模板函数可以和一个与其同名的函数模板共存，并且这个同名的函数模板可以被实例化为与非模板函数具有相同类型的调用参数**。
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

2. a由于**函数模板的模板参数推断时不允许自动类型转换，而非模板函数是允许的**.因此最后一个调用会选择非模板参函数;
 
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
//
```