
- [const](#const)
  - [1、c++ 在函数后加const的意义](#1c-在函数后加const的意义)
  - [2、c++ 函数前面和后面使用const 的作用](#2c-函数前面和后面使用const-的作用)

------
## const  
### 1、c++ 在函数后加const的意义
　　
表示这些函数是"只读"函数, 加上const关键字进行标识.
<font color=orange>
- 非静态成员函数后面加const
  - 加到**非类成员函数**或**类静态成员**后面会产生编译错误  
</font>  
<font color = green>
- 表示成员函数隐含传入的this指针为const指针，决定了在该成员函数中，任意修改它所在的类的成员的操作都是不允许的（因为隐含了对this指针的const引用）;
</font>  
<font color=deepred>  
- 唯一的例外是对于mutable修饰的成员。  
    1、加了const的成员函数可以被非const对象和const对象调用  
    2、但不加const的成员函数只能被非const对象调用  
</font>  

### 2、c++ 函数前面和后面使用const 的作用

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
