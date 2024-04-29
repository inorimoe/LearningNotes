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

如果要给函数内的全局变量赋值，必须使用 `global` 关键字标识。
使用 `nonlocal` 关键字来指示变量来自于嵌套作用域，即 `nonlocal` 语句标识出以前引用绑定的变量, 在除global变量外的作用域中。

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

## 字符串  
1. python 字符串用`'`和`"`进行标识。
```python
str1 = 'hello, world!'
str2 = "hello, world!"
str3 = """             
        hello, 
        world!
        # 以三个双引号或单引号开头的字符串可以折行
        """
```
2. python 在字符串中使用`\`来表示转义字符，语法规则与C一致。  
3. python字符串运算符 与 语法糖：
    - `+` 运算符实现字符串的 __拼接__。
    - `*` 运算符来 __重复__ 一个字符串。
    - `in` 和 `not in` 来判断一个字符串是否 __包含__ 另外一个字符串。
    - `[]` 和 `[:]` 运算符从字符串取出某个字符或某些字符, 进行 __切片__ 操作。
```python
运算符：
s1 = 'hello ' * 3          # s1 == 'hello hello hello '
print('good' in s1)        # False

str = "abc123456"
print(str[2])               # c
# 字符串切片(从指定的开始索引到指定的结束索引)
print(str[2:5])             # c12
print(str[2:])              # c123456
print(str[2::2])            # c246
print(str[::2])             # ac246
print(str[::-1])            # 654321cba
print(str[-3:-1])           # 45

语法糖：
str1 = 'hello, world!'
# 通过内置函数len计算字符串的长度
print(len(str1))  # 13

# 获得字符串首字母大写的拷贝
print(str1.capitalize()) # Hello, world!

# 获得字符串每个单词首字母大写的拷贝
print(str1.title()) # Hello, World!

# 获得字符串变大写后的拷贝
print(str1.upper()) # HELLO, WORLD!

# 从字符串中查找子串所在位置
print(str1.find('or')) # 8
print(str1.find('shit')) # -1

# 与find类似但找不到子串时会引发异常
# print(str1.index('or'))
# print(str1.index('shit'))

# 检查字符串是否以指定的字符串开头
print(str1.startswith('He')) # False
print(str1.startswith('hel')) # True

# 检查字符串是否以指定的字符串结尾
print(str1.endswith('!')) # True

# 将字符串以指定的宽度居中并在两侧填充指定的字符
print(str1.center(50, '*'))

# 将字符串以指定的宽度靠右放置左侧填充指定的字符
print(str1.rjust(50, ' '))

str2 = 'abc123456'
# 检查字符串是否由数字构成
print(str2.isdigit())  # False

# 检查字符串是否以字母构成
print(str2.isalpha())  # False

# 检查字符串是否以数字和字母构成
print(str2.isalnum())  # True

str3 = '  123456789   '
print(str3)
# 获得字符串修剪左右两侧空格之后的拷贝
print(str3.strip())
```

4. python 字符串的格式化输出：
```python
a, b = 5, 10

print('%d * %d = %d' % (a, b, a * b))           #  "..." %（...）
print('{0} * {1} = {2}'.format(a, b, a * b))    #  "...".format(...)
print(f'{a} * {b} = {a * b}')                   #  f"...{var1}...{var2}...{var3}"
```

## 列表
pyhton 列表：
- 将列表的元素放在[]中，多个元素用, 进行分隔。
- 可以使用for循环对列表元素进行遍历。
- 可以使用 `[]` 或 `[:]` 运算符取出列表中的一个或多个元素。

### 列表的增删查改
```python
初始化
list = [1,3,5,7]

重复
list2 = list * 3      # [1,2,3,1,2,3,1,2,3]

长度
len(list)                   # 4

下标
list[0]                     # 1
list[3]                     # 7
list[99]                    # IndexError: list index out of range
list[-1]                    # 7

循环：
1、下标遍历：
for index in range(len(list)):
    print(list[index])
2、for遍历：
for elem in list:
    print(elem)
3、enumerate函数遍历：
for index, elem in enumrate(list):
    print(index, elem)

添加、插入
list.append(999)
list.insert(1, 999)

合并
list.extend([111,222,333])
list += [111,222,333]

查
if 999 in list :
    ...

删除
1、删除指定数值：
list.remove(999)
2、在指定位置删除元素
list.pop(0)
list.pop(len(list)-1)
3、清空列表
list.clear()
```

### 列表的切片

```python
fruits = ['grape', 'apple', 'strawberry', 'waxberry']
fruits += ['pitaya', 'pear', 'mango']
print(fruits)

#切片:
fruits2 = fruits[1:3]
print(fruits2)
fruits3 = fruits[-3:-1]
print(fruits3)

# 通过完整切片操作来复制列表
fruits4 = fruits[:]
print(fruits4)
# 步长设置-1，获得倒装列表
fruits5 = fruits[::-1]
print(fruits5)

--- print out ---
['grape', 'apple', 'strawberry', 'waxberry', 'pitaya', 'pear', 'mango']
['apple', 'strawberry']
['pitaya', 'pear']
['grape', 'apple', 'strawberry', 'waxberry', 'pitaya', 'pear', 'mango']
['mango', 'pear', 'pitaya', 'waxberry', 'strawberry', 'apple', 'grape']
```

### 列表的排序

```python
list = ['orange', 'apple', 'zoo', 'inter','nation', 'blueberry']

# sorted 函数返回排序后的列表拷贝
list2 = sorted(list)
print(list2)

# 逆序
print( sorted(list, reverse= True) )

# 通过 key 关键字参数指定排序类型，默认字母表顺序 or 字符串长度
list3 = sorted(list, key=len)
print(list3)

# 直接在列表原对象上进行排序
list.sort(reverse=True)
print(list)

--- print out ---
['apple', 'blueberry', 'inter', 'nation', 'orange', 'zoo']
['zoo', 'orange', 'nation', 'inter', 'blueberry', 'apple']
['zoo', 'apple', 'inter', 'orange', 'nation', 'blueberry']
['zoo', 'orange', 'nation', 'inter', 'blueberry', 'apple']
```
### 列表的生成式语法
```python
import sys
f = [x for x in range(1, 10)]
print(f)
f = [x + y for x in 'ABCDE' for y in '1234567']
print(f)
# 用列表的生成表达式语法创建列表容器
# 用这种语法创建列表之后元素已经准备就绪所以需要耗费较多的内存空间
f = [x ** 2 for x in range(1, 100)]
print(sys.getsizeof(f))  # 查看对象占用内存的字节数
print(len(f))

--- print out ---

[1, 2, 3, 4, 5, 6, 7, 8, 9]
['A1', 'A2', 'A3', 'A4', 'A5', 'A6', 'A7', 'B1', 'B2', 'B3', 'B4', 'B5', 'B6', 'B7', 'C1', 'C2', 'C3', 'C4', 'C5', 'C6', 'C7', 'D1', 'D2', 'D3', 'D4', 'D5', 'D6', 'D7', 'E1', 'E2', 'E3', 'E4', 'E5', 'E6', 'E7']
920
99
```

## 生成器
在Python中，这种一边循环一边计算的机制，称为生成器：generator
初始化：
1、只要把一个列表生成式的[]改成()，就创建了一个generator：
```py
L = [x * x for x in range(10)]  # L 是列表
g = (x * x for x in range(10))  # g 是生成器：generator
```
2、如果一个函数定义中包含yield关键字，那么这个函数就不再是一个普通函数，而是一个generator函数，调用一个generator函数将返回一个generator：
```py
def fib(max):
    n, a, b = 0, 0, 1
    while n < max:
        yield b
        a, b = b, a + b
        n = n + 1
    return 'done'

gn = fib(number)   # gn 是 generator
```
执行：
1、在每次调用next()的时候执行，遇到yield语句返回，再次执行时从上次返回的yield语句处继续执行。
2、通过next()函数获得generator的下一个返回值。
```py
cnt = 3 
gn = fib(cnt)
rgn = fib(cnt)
for ret in gn:
    print(ret)
for index in range(cnt):
    print(next(rgn))
lgn = fib(10)
print(list(lgn))

--- prit out ---
1
1
2
1
1
2
[1, 1, 2, 3, 5, 8, 13, 21, 34, 55]
```

# 元组、集合、字典