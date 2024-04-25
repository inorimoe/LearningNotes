# Python 语法手册

## 变量和类型
Python中的数据类型很多，而且允许自定义新的数据类型，以下是几种常用的数据类型：
* 整型：Python中可以处理任意大小的整数。
* 浮点型：支持数学写法（如123.456），还支持科学计数法（如1.23456e2）。
* 字符串型：字符串是以单引号或双引号括起来的任意文本。
* 布尔型：布尔值只有True、False两种值。
* 复数型：形如3+5j，跟数学上的复数表示一样，唯一不同的是虚部的i换成了j。这个类型并不常用.

## 命名规则
* 字母（广义的Unicode字符，不包括特殊字符）、数字和下划线构成，数字不能开头
* 大小写敏感，不要跟关键字(基础库的名字)冲突
* 受保护的实例属性用单个下划线开头，私有的实例属性用两个下划线开头

## 基础类型转换

```py
* int() #将一个数值或字符串转换成整数，可以指定进制。
* float() #将一个字符串转换成浮点数。
* str() #将指定的对象转换成字符串形式，可以指定编码。
* chr() #将整数转换成该编码对应的字符串（一个字符）。
* ord() #将字符串（一个字符）转换成对应的编码（整数）。
```
## 基础IO函数
```py
input()  #函数获取键盘输入(字符串)
print()  #函数输出带占位符的字符串
print("%d, %s, %.*f"%(varInt , varString,  varFloat)) out写法，占位符%_与c类似。
#格式化输出多样，详细内容请参考官方文档；
```
## 运算符
|最小优先^|运算符|描述|
|:-:|:-:|:-:|
|1|`[]` `[:]`|下标，切片|
|2|`**`	|指数|
|3|`~` `+` `-`|按位取反, 正负号|
|4|`*` `/` `%` `//` |乘，除，模，整除|
|5|`+` `-`|加，减|
|6|`>>` `<<`|右移，左移|
|7|`&`	|按位与|
|8|`^` `\|`	|按位异或，按位或|
|9|`<=`  `<` `>` `>=`	|小于等于，小于，大于，大于等于|
|10|`==` `!=`	|等于，不等于|
|11|`is` `is not`	|身份运算符|
|12|`in` `not in`	|成员运算符|
|13|`not` `or` `and`	|逻辑运算符|
|14|`=` `+=` `-=` `*=` `/=` `%=` `//=` `**=` `&=` |`=`  `^=`   `>>=` `<<=`|

## 分支语句
* `if...elif...else...`结构 或 `if...else...`结构
* py 使用了缩进的方式来表示代码的层次结构
```py
if x > 0:
    ...
elif x > -1:
    ...
elif x < -10:
    ...
else:
    ...
```

## 循环语句
* `for ... in ...`语句
* `while True/False/statement：`
```py
sum = 0
for x in range(101):
    sum += x
print(sum)
------
range(n): 产生[0, n);
range(n, m): 产生[n, m);
range(n, m, i): 产生[n, m), i是递增递减的值；
-------------
-------------
sum2 = 0
while True:
    ...
    sum2 += 1
    break
print(sum2)
```

## 函数
### 函数定义
在Python中，使用`def`关键字定义函数，函数命名遵循变量命名规则。
函数参数放在圆括号中，类似数学函数的自变量。
通过return关键字返回值，相当于数学中的因变量。
```py
def fnc(num):
    result = num + 1
    return result
print(fnc(0)) // 调用函数
```
### 函数参数
在Python中，函数的参数可以有 _默认值_ ，也支持使用 _可变参数_  。

__默认值__: 参数定义时赋值。
```py 
from random import randint
def roll_n_dice(n = 6):
    """摇n个筛子"""
    for _ in range(n):
        total += randint(1, 6)
    return total

def add(a=0, b=0, c=0):
    """three number sum"""
    return a + b + c

print(roll_n_dice()) #没有指定参数传参, 那么使用默认值
print(add(1)) #传参给a，其余使用默认值
print(add(c=11, b=22, a=33)) #传递参数时可以不按照设定的顺序进行传递
```
__可变参数__: 在参数名前面添加*进行表示。
```py 
# 在参数名前面的*表示args是一个可变参数
def add(*args):
    total = 0
    for val in args:
        total += val
    return total

# 在调用add函数时可以传入0个或多个参数
print(add())
print(add(1))
print(add(1, 2))
print(add(1, 2, 3))
print(add(1, 3, 5, 7, 9))
```
### 模块管理函数
Python不支持函数重载，后定义的函数会覆盖先前的同名函数。
不过，在不同模块中可以有同名函数，通过import关键字导入模块来区分使用哪个模块的函数。
_module1.py_
```py
def foo():
    print('hello, world!')
```
_module2.py_
```py
def foo():
    print('goodbye, world!')
```
```py
函数覆盖
from module1 import foo
foo() # 输出hello, world!
from module2 import foo
foo() # 覆盖hello，输出goodbye, world!

from module1 import foo
from module2 import foo
foo() # 覆盖hello，输出goodbye, world!

函数区分
import module1 as m1
import module2 as m2
m1.foo()
m2.foo()
```
## 模块

0. Python 模块(Module)，是.py文件，包含了 Python 对象定义和 Python 执行语句。
1. 如果我们导入的模块除了定义函数之外还有可以执行代码，那么Python解释器在导入这个模块时就会执行这些代码。
2. 为避免在导入模块时执行其中的可执行代码，应将这些代码放在`if __name__ == "__main__":`条件内，确保它们只在该模块被直接运行时执行。
3. `__name__`是Python中一个隐含的变量, 它代表了模块的名字。
4. 只有被Python解释器 __直接执行的模块__ 的名字才是`__main__`。

`module3.py`
```py
def foo():
    pass
def bar():
    pass
# __name__是Python中一个隐含的变量它代表了模块的名字
# 只有被Python解释器直接执行的模块的名字才是__main__
if __name__ == '__main__':
    print('call foo()')
    foo()
    print('call bar()')
    bar()
```
`run.py`
```py
import module3
# 导入module3时, 不会执行模块中if条件成立时的代码, 因为模块的名字是module3而不是__main__
# 这就模块经常出现if __name__ == '__main__':语句的原因。
```
## 变量的生命周期以及作用域  
* python 使用了缩进的方式来表示代码的层次结构
* 变量的生命周期取决于代码的层次结构（类似C）

如果要给函数内的全局变量赋值，必须使用 global 关键字标识。
使用nonlocal关键字来指示变量来自于嵌套作用域，即 nonlocal 语句使列出的标识符，引用除global变量外的作用域中的以前绑定的变量。

```py
count = 1
cnt = 0
def a():
    count = 12
    cnt = 123  
    def b():
        nonlocal count
        global cnt
        count = 999
        cnt = 888
        print(cnt)
    b()
    print(cnt)
    print(count)
a()
print(count)
print(cnt)
---输出
888
123
999
1
888
```