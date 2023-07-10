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
1.如果调用参数**引用传递**的，任何类型转换都不被允许。通过模板类型参数 T 定义的两个参数，它们实参的类型必须完全一样。
```C++
template<typename T>
T max (T & a, T const& b){
return a;
}
int main(void){
    const int i = 3;
    int j = 4;
    int k = 5;
    max(j, k); //compiler success (test推断成max(int&, int&))需要vs2022验证
    max(i, j); //compiler error, 推断成max(const int&, int&)
    std::cout<<i;
    return 0;
}
```
2.如果调用参数是**按值传递**的，那么只有退化（decay）这一类简单转换是被允许的：

>* const 和 volatile 限制符会被忽略.
>* 引用被转换成被引用的类型.
>* raw array 和函数被转换为相应的指针类型.

通过模板类型参数 T 定义的两个参数，它们实参的类型在退化（decay）后必须一样。
