# 关于C++模板的笔记
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
