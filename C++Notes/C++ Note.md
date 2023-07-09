
- [c++ 在函数后加const的意义：](#c-在函数后加const的意义)
- [c++ 函数前面和后面 使用const 的作用：](#c-函数前面和后面-使用const-的作用)
------
### c++ 在函数后加const的意义：
　　我们定义的类的成员函数中，常常有一些成员函数不改变类的数据成员，也就是说，这些函数是"只读"函数，而有一些函数要修改类数据成员的值。如果把不改变数据成员的函数都加上const关键字进行标识，显然，可提高程序的可读性。其实，它还能提高程序的可靠性，已定义成const的成员函数，一旦企图修改数据成员的值，则编译器按错误处理。 const成员函数和const对象 实际上，const成员函数还有另外一项作用，即常量对象相关。对于内置的数据类型，我们可以定义它们的常量，用户自定义的类也一样，可以定义它们的常量对象。

- <font color=orange>非静态成员函数后面加const（*加到非成员函数或静态成员后面会产生编译错误*）</font>
- <font color=green>表示成员函数隐含传入的this指针为const指针，决定了在该成员函数中，任意修改它所在的类的成员的操作都是不允许的（因为隐含了对this指针的const引用）;</font>
- <font color=deepred>唯一的例外是对于mutable修饰的成员。  
    1、加了const的成员函数可以被非const对象和const对象调用
    2、但不加const的成员函数只能被非const对象调用
</font>

### c++ 函数前面和后面 使用const 的作用：
- <font color=red>前面使用 const 表示返回值为 const</font>
- 后面加 const表示函数不可以修改class的成员

```c++ 
//成员函数后加const可重载
#include <iostream>
using namespace std;
class Multiplier {
    int m_;
public:
    // constructor:
    explicit constexpr Multiplier(int m) noexcept : m_{ m } {}
    // call operator:
    constexpr int operator () (int x) const noexcept { return m_ * x; };
    constexpr int operator () (int x) noexcept { return m_ * 2 * x; };
};
int main()
{
    cout << "Hello World" << endl;
    const Multiplier CM(1);
    Multiplier M(1);
    const int cm = CM(2);
    int m = M(2);
    cout << CM(m) << "  " << M(m);
    return 0;
}
```


