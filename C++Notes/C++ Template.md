### 关于C++模板的笔记
# 函数模板
## 定义模板
`template< 由逗号分割的模板参数>`
模板参数是 typename T;
关键字 typename 标识了一个类型参数 T. 类型参数可以任意标识，习惯上用 T;
```c++
template< typename T >
```
## 两阶段编译检查
在定义没有报错误提示，模板是被分两步编译:
1.在模板定义阶段，模板的检查并不包含类型参数的检查。只包含下面几个方面:
> * 语法检查
> * 使用了未定义的不依赖于模板参数的名称(类型名，函数名)
> * 未使用模板参数的 static assertions

2.在模板实例化阶段, 模板会再次被检查;
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
2. 如果调用参数是**按值传递**的，那么只有退化（decay）这一类简单转换是被允许的：

>* const 和 volatile 限制符会被忽略.
>* 引用被转换成被引用的类型.
>* raw array 和函数被转换为相应的指针类型.

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
## 模板的返回类型
C++提供了多种应对这一问题的方法：
1. 引入额外的模板参数作为返回类型。
2. 让编译器找出返回类型。
3. 将返回类型定义为两个参数类型的“公共类型”
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
### 返回类型推断(C++14)