- [Python 语法手册](#python-语法手册)
- [基础语法](#基础语法)
  - [变量和类型](#变量和类型)
  - [命名规则](#命名规则)
  - [基础类型转换](#基础类型转换)
  - [基础IO函数](#基础io函数)
  - [运算符](#运算符)
  - [分支语句](#分支语句)
  - [循环语句](#循环语句)
  - [函数](#函数)
    - [函数定义](#函数定义)
    - [函数参数](#函数参数)
    - [模块管理函数](#模块管理函数)
  - [模块](#模块)
  - [变量的生命周期以及作用域](#变量的生命周期以及作用域)
  - [字符串](#字符串)
  - [列表](#列表)
    - [列表的增删查改](#列表的增删查改)
    - [列表的切片](#列表的切片)
    - [列表的排序](#列表的排序)
    - [列表的生成式语法](#列表的生成式语法)
  - [生成器](#生成器)
  - [元组](#元组)
  - [集合](#集合)
  - [字典](#字典)
- [面向对象（Object-Oriented Programming）](#面向对象object-oriented-programming)
  - [类（Class）](#类class)
  - [创建和运行对象](#创建和运行对象)
  - [类成员访问可见性](#类成员访问可见性)
  - [@property装饰器](#property装饰器)
  - [`__slots__`语法](#__slots__语法)
  - [类方法 @classmethod](#类方法-classmethod)
  - [静态方法 @staticmethod](#静态方法-staticmethod)
  - [继承](#继承)
    - [基本概念](#基本概念)
    - [继承语法](#继承语法)
  - [方法重写（Override）](#方法重写override)
  - [方法重载（Overload）](#方法重载overload)
    - [1. 使用默认参数和关键字参数](#1-使用默认参数和关键字参数)
    - [2. 使用可变参数 `*args` 和 `**kwargs`](#2-使用可变参数-args-和-kwargs)
    - [3. 使用单分派泛函数 `functools.singledispatch`](#3-使用单分派泛函数-functoolssingledispatch)
    - [4. 使用类和多分派 `functools.singledispatchmethod`](#4-使用类和多分派-functoolssingledispatchmethod)
    - [5. 使用第三方库如 `multipledispatch`](#5-使用第三方库如-multipledispatch)
    - [总结](#总结)
  - [使用 `super()` 调用父类方法](#使用-super-调用父类方法)
  - [多重继承](#多重继承)
    - [方法调用解析顺序（MRO）](#方法调用解析顺序mro)
  - [抽象基类](#抽象基类)
    - [总结](#总结-1)

# Python 语法手册
# 基础语法
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
列表生成式的基本语法：
```py
基本语法结构：
 [表达式 for 变量 in 可迭代对象] 
or 加入条件判断：
 [表达式 for 变量 in 可迭代对象 if 条件]
```
列表生成式的用法：
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
2、通过调用next()函数获得generator的下一个返回值。
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
## 元组
Python中的元组是一种容器数据类型，与列表的区别在于其不可变的特性。
元组的创建：
```python
# 使用圆括号创建元组
tup = (1, 2, 3)
print(tup)  # 输出：(1, 2, 3)

# 使用tuple()函数创建元组
tup = tuple([1, 2, 3])
print(tup)  # 输出：(1, 2, 3)

# 直接使用逗号创建元组
tup = 1, 2, 3
print(tup)  # 输出：(1, 2, 3)

# 创建空元组
empty_tup = ()
print(empty_tup)  # 输出：()

# 注意赋值的情况
value = （1）
print(value)   # 输出：1 ，注意这种括号内单个元素，会退化成赋值

# 读取元组的元素
print(tup[0])

# 遍历元组中的值
for member in tup:
    print(member)

# 元组的不可变性
tup[0] = -1 # 错误，无法修改，提示TypeError

# 元组可以重新赋值，原来元组被垃圾回收
tup = (2, 3, 4)

# 元组可以类型转换成列表
lst = list(tup)

# 同理，列表可以类型转换成元组
tup = tuple(lst)

# 注意，不可修改的特性只存在于定义的那层级
tup = (1, [3,4,5], 3)
tup[1][1] = -1
print(tup)  # 输出：(1, [3, -1, 5], 3) ,元素列表的元素可被修改 
```

## 集合
Python中的集合跟数学上的集合是一致的，不允许有重复元素，而且可以进行交集、并集、差集等运算。
```py
# 创建集合：可以使用set()函数或者大括号 {} 来创建一个集合。
s = set([1, 2, 3, 4, 5])
set1 = {1, 2, 3, 4, 5}
set2 = set(range(1, 10))    
set3 = set((1, 2, 3, 3, 2, 1))
set4 = {num for num in range(1, 100) if num % 3 == 0 or num % 5 == 0}

# 添加元素：使用 add() 方法可以添加单个元素，update() 方法可以添加多个元素。
s.add(6)
s.update([7, 8, 9])

# 删除元素：remove() 方法可以删除指定的元素，如果元素不存在会抛出错误。discard() 方法也可以删除指定的元素，但如果元素不存在，它不会抛出错误。
s.remove(6)
s.discard(7)

# 检查元素：可以使用 in 关键字来检查元素是否存在于集合中。
if 1 in s:
    print("1 is in the set")

# 集合运算：集合支持并集（union）、交集（intersection）、差集（difference）和对称差集（symmetric_difference）等运算。
s1 = {1, 2, 3}
s2 = {2, 3, 4}
print(s1.union(s2))                 # 并集 {1, 2, 3, 4}
print(s1.intersection(s2))          # 交集 {2, 3}
print(s1.difference(s2))            # 差集 {1}
print(s1.symmetric_difference(s2))  # 对称差集 {1, 4}
```

## 字典
在Python中，字典（dict）是一种可变的、可索引的、无序的数据类型，它存储键值对（key-value pairs）。
- 字典的键必须是不可变的类型，如字符串、数字或元组。
- 字典的值可以是任何Python数据类型。
```py
# 创建字典：
    # 通常写法：
    d = {'name': 'John', 'age': 30, 'city': 'New York'}
    # 创建字典的构造器语法
    items1 = dict(one=1, two=2, three=3, four=4)
    # 通过zip函数将两个序列压成字典
    items2 = dict(zip(['a', 'b', 'c'], '123'))
    # 创建字典的推导式语法
    items3 = {num: num ** 2 for num in range(1, 10)}

# 访问元素：可以通过键来访问字典中的值。
    # 普通写法：
    print(d['name'])  # 输出 'John'
    # get() 方法：不会引发 KeyError 异常
    dict.get(key, default=None) # 访问指定kv对
        1、key：要从字典中检索的键。
        2、default（可选）：如果字典中不存在该键，将返回此默认值。如果没有指定，默认值为 None。
# 修改元素：可以通过键来修改字典中的值。
d['age'] = 31
# 添加元素：可以通过新的键来添加元素。
d['job'] = 'Engineer'
# 删除元素：del语句可以删除字典中的元素，clear()方法可以清空字典。
    # 普通写法
    del d['age']
    d.clear()
    # pop方法
    dict.popitem()   # 弹出字典尾部元素
    dict.pop(key, default=None)  # 删除指定kv对
        1、key：要从字典中删除并返回其值的键。
        2、default（可选）：如果字典中不存在该键，将返回此默认值。如果没有指定，默认值为 None。
# 检查键是否存在：可以使用in关键字来检查键是否存在于字典中。
if 'name' in d:
    print("Key 'name' is in the dictionary")
#获取所有键和值：keys()方法可以返回所有的键，values()方法可以返回所有的值，items()方法可以返回所有的键值对。
print(d.keys())
print(d.values())
print(d.items())
```

# 面向对象（Object-Oriented Programming）

## 类（Class）

1. __init__是python类的构造函数。
2. 成员函数的首参数需要设置为self。
3. 类变量：是所有类对象共有，即静态变量。
4. 实例变量(类属性)：是所属对象的实例私有。
5. 类变量在实例会被同名的实例变量(类属性)覆盖。

```py

class Student(object):
    # 类变量
    var = 42  

    def __init__(self, name, weight):
        # 实例变量(类属性)
        self.name = name
        self.weight = weight

    def study(self, course_name, minutes):
        self.var = minutes
        print('%s正在学习%s, 花了%s分钟.' % (self.name, course_name, self.var))

```

## 创建和运行对象
```py
def main():
    stu = Student("小学生", 200)
    stu.study("负重", 10)
    print (stu.var)

    stu2 = Student("中学生", 400)
    print ("共有的类变量为：%d"%stu2.var) # 共有的类变量
    
    Student.var = 99
    print ("类变量被修改为：%d"%stu2.var) # 类变量被修改

if __name__ == '__main__':
    main()
```

## 类成员访问可见性
1. 公开（Public）：
   1. 如果一个变量名或方法名没有前缀下划线，那么它就是公开的。
   2. 这意味着这些变量和方法可以被类的实例以及类的外部直接访问。
2. 受保护（Protected）：
   1. 如果一个变量名或方法名以单下划线` _ `开头，那么它就是受保护的。
   2. 这意味着这些变量和方法<b>不推荐不应该</b>被类的外部访问，但是在Python中并<b>没有强制限制</b>.
3. 私有（Private）：
   1. 如果一个变量名或方法名以双下划线` __ `开头，那么它就是私有的。
   2. 这意味着这些变量和方法<b>不能</b>被类的外部直接访问。
4. 私有特性：
   1. Python并没有真正实现私有，而是通过改变名字（Name Mangling）的方式来实现的。
   2. `__variable`会被改变为`_ClassName__variable12`。
```py
class TestIsVisible(object):
    def __init__(self, visible, invisible, non_know):  
        self.visible = visible
        self.__invisible = invisible
        self._visible = non_know

visible_object = TestIsVisible("can see",  "can not see",  "non know if visible")
print(visible_object.visible)  # 输出: can see
print(visible_object._visible)  # 输出: non know if visible
print(visible_object.__dict__)  # 输出: {'visible': 'can see', '_TestIsVisible__invisible': 'can not see', '_visible': 'non know if visible'}
print(visible_object._TestIsVisible__invisible)  # 输出: can not see
"""
" visible是公开的，_visible是受保护的，__invisible是私有的。
" 尽管__invisible是私有的，但我们仍然可以通过_TestIsVisible__invisible来访问它
"""
```

## @property装饰器

@property装饰器：用于为访问保护属性定义method（即getter访问器、setter设置器和deleter删除器），使得访问属性不用加括号`（）`;
* getter标识: @property
* setter标识: @属性名.setter
* deleter标识: @属性名.deleter

```py
class MyClass(object):
    def __init__(self, x):
        self._x = x

    @property         # Getters 访问器
    def x(self):
        return self._x

    @x.setter         # Setters 设置器
    def x(self, value):
        self._x = value

    @x.deleter        # Deleters 删除器
    def x(self):
        del self._x

obj = MyClass(42)
obj.x += 1
print(obj.x)
del obj.x
```

## `__slots__`语法  

在Python中，`__slots__`是一个特殊的类属性，通过限制实例的动态属性，用于优化实例的内存使用和提高性能。
Python解释器就不需要为每个实例动态创建一个字典（`__dict__`）来存储属性，而是为每个实例分配固定的内存空间来存储这些属性。
基本用法：要使用`__slots__`，只需在类定义中添加一个包含属性名称的元组或列表即可。

```py
class MyClass(object):
    __slots__ = ('name', 'age')

    def __init__(self, name, age):
        self.name = name
        self.age = age
```

注意事项：

- 使用`__slots__`会限制实例的动态属性。一旦为类定义了`__slots__`，除非在`__slots__`中声明，否则实例不能动态地添加新属性。
- `__slots__`应该谨慎使用，特别是在定义子类时。如果子类没有定义`__slots__`，但父类有，那么子类实例仍然会有一个`__dict__`，因为子类需要存储继承自父类的任何属性。
- 对于需要频繁添加或删除属性的对象，或者需要完全动态属性的对象，使用`__slots__`可能不是最佳选择。

## 类方法 @classmethod

@classmethod 是一个装饰器，它用来指定一个函数为类的方法，这意味着这个方法属于类而非类的实例。

特点：

- 函数接收类 `cls` 作为第一个参数，表示类本身。这点区别于接收`self`的普通函数。  
- 类方法可通过类直接调用`类名.函数名()`，或类实例对象调用`类对象.函数名（）`  

常见用途：

- 工厂方法：用于在类的内部定义多种创建对象的方式。
- 类方法可修改类变量：表示这种修改对所有类实例对象都有影响。

```py
from time import time, localtime, sleep
class Clock(object):
    """数字时钟"""
    cnt = 0
    def __init__(self, hour=0, minute=0, second=0):
        self._hour = hour
        self._minute = minute
        self._second = second

    @classmethod
    def now(cls):
        cls.cnt += 1
        ctime = localtime(time())
        return cls(ctime.tm_hour, ctime.tm_min, ctime.tm_sec)
    
    def show(self):
        """显示时间"""
        return '%02d:%02d:%02d' % \
               (self._hour, self._minute, self._second)
def main():
    # 通过类方法创建对象并获取系统时间
    clock = Clock.now()
    print(clock.show())

if __name__ == '__main__':
    main()
```

## 静态方法 @staticmethod

在 Python 中，@staticmethod 是一个内置的装饰器，用于定义一个类中的静态方法。
静态方法不接收隐式的第一个参数（通常是 self 或 cls），这意味着它不依赖于类实例的状态。因此，静态方法既不需要类实例也不需要类本身作为前置参数。

- 不接受` self `或` cls `参数。
- 因为没有传递`self`参数进入, 所以无法访问或修改类的变量。
- 可通过类直接调用`类名.函数名()`

```python
class Triangle(object):

    def __init__(self, a, b, c):
        self._a = a
        self._b = b
        self._c = c

    @staticmethod
    def is_valid(a, b, c):
        return a + b > c and b + c > a and a + c > b

def main():
    a, b, c = 3, 4, 5
    if Triangle.is_valid(a, b, c):
        t = Triangle(a, b, c)
    else:
        print('无法构成三角形.')

if __name__ == '__main__':
    main()
```  

## 继承  
Python 中的类继承是面向对象编程的一个核心概念，它允许我们定义一个类（子类或派生类）继承另一个类（父类或基类）的属性和方法。这样做的主要目的是实现代码的重用，同时也可以在子类中添加或修改属性和方法，从而扩展功能。

### 基本概念

- **父类（基类）**：被继承的类。
- **子类（派生类）**：继承自父类的类。
- **方法重写（Override）**：子类提供父类中有的方法的一个新版本。
- **方法重载（Overload）**：Python 不直接支持传统意义上的方法重载，但可以通过默认参数等方式达到类似效果。
- **`super()`函数**：用于调用父类的方法。

### 继承语法

```python
class BaseClass:
    # Body of base class
    pass

class DerivedClass(BaseClass):
    # Body of derived class
    pass
```

## 方法重写（Override）

假设我们有一个基类 `Animal`，这个类有一些基本的方法和属性。我们想定义一个 `Dog` 类来继承 `Animal` 类的功能，并添加一些独有的功能。

```python
class Animal:
    def __init__(self, name):
        self.name = name
    
    def speak(self):
        raise NotImplementedError("Subclass must implement abstract method")

class Dog(Animal):
    def speak(self):
        return f"{self.name} says Woof!"
```

在这个例子中，`Dog` 类继承了 `Animal` 类。我们重写了 `speak` 方法来提供狗的叫声。

## 方法重载（Overload）

**Python 本身不支持传统的函数重载。**

在许多传统的静态类型语言中，如 C++ 和 Java，函数重载允许同一函数名在同一作用域内有多个不同的实现，它们通过参数的数量和类型的不同来区分。
然而，Python 作为一种动态类型语言，不支持这种传统意义上的函数重载。因为在 Python 中，函数的参数是动态检查的，不需要指定类型，并且同一个标识符在同一作用域内不能多次定义。

尽管 Python 本身不支持传统的函数重载，但我们可以通过一些技术手段模拟出类似的功能。以下是几种在 Python 中实现函数“重载”行为的方法。

### 1. 使用默认参数和关键字参数

最简单的方式是使用默认参数和可变参数。这种方式可以让一个函数根据提供的参数数量和类型表现出不同的行为。

```python
def greet(name, msg="Hello"):
    print(f"{msg}, {name}")

greet("Alice")            # 输出: Hello, Alice
greet("Bob", "Goodbye")   # 输出: Goodbye, Bob
```

### 2. 使用可变参数 `*args` 和 `**kwargs`

通过 `*args` 和 `**kwargs`，我们可以让一个函数接受任意数量的参数，从而在函数内部根据参数的不同实现不同的功能。

```python
def greet(*args):
    if len(args) == 1:
        print(f"Hello, {args[0]}")
    elif len(args) == 2:
        print(f"{args[1]}, {args[0]}")

greet("Alice")            # 输出: Hello, Alice
greet("Bob", "Goodbye")   # 输出: Goodbye, Bob
```

### 3. 使用单分派泛函数 `functools.singledispatch`

Python 标准库中的 `functools` 模块提供了一个装饰器 `functools.singledispatch`，它可以将普通函数转换成一个单分派泛函数。这允许根据第一个参数的类型使用不同的实现，适用于那些希望根据参数类型改变行为的函数。

```python
from functools import singledispatch

@singledispatch
def greet(arg):
    print(f"Hello, {arg}")

@greet.register(int)
def _(arg):
    print(f"Hello, number {arg}")

@greet.register(list)
def _(arg):
    print("A list with values: " + ", ".join(map(str, arg)))

greet("Alice")            # 输出: Hello, Alice
greet(42)                 # 输出: Hello, number 42
greet(["Alice", "Bob"])   # 输出: A list with values: Alice, Bob
```

### 4. 使用类和多分派 `functools.singledispatchmethod`

对于类的方法，Python 3.8 引入了 `functools.singledispatchmethod` 装饰器，用于支持基于类型的多分派。

```python
from functools import singledispatchmethod

class Greeter:
    @singledispatchmethod
    def greet(self, arg):
        print(f"Hello, {arg}")

    @greet.register(int)
    def _(self, arg):
        print(f"Hello, number {arg}")

    @greet.register(list)
    def _(self, arg):
        print("A list with values: " + ", ".join(map(str, arg)))

g = Greeter()
g.greet("Alice")            # 输出: Hello, Alice
g.greet(42)                 # 输出: Hello, number 42
g.greet(["Alice", "Bob"])   # 输出: A list with values: Alice, Bob
```

### 5. 使用第三方库如 `multipledispatch`

`multipledispatch` 是一个强大的第三方库，支持多参数的多分派。这可以让你根据多个参数的类型来重载函数。

安装 `multipledispatch`：

```bash
pip install multipledispatch
```

使用 `multipledispatch`：

```python
from multipledispatch import dispatch

@dispatch(str)
def greet(name):
    print(f"Hello, {name}")

@dispatch(str, str)
def greet(name, msg):
    print(f"{msg}, {name}")

greet("Alice")             # 输出: Hello, Alice
greet("Bob", "Goodbye")    # 输出: Goodbye, Bob
```

### 总结

虽然 Python 不支持传统的函数重载，但通过上述方式可以实现类似的功能。这些技术可以根据需要灵活使用，以提供更丰富的函数行为。在实际应用中，选择适合的方式可以让你的代码更加通用和强大。

## 使用 `super()` 调用父类方法

如果我们想在子类中调用父类的方法，可以使用 `super()` 函数。

```python
class Animal:
    def __init__(self, name):
        self.name = name

class Dog(Animal):
    def __init__(self, name, breed):
        super().__init__(name)  # 调用父类的 __init__ 方法
        self.breed = breed

    def speak(self):
        return f"{self.name} the {self.breed} says Woof!"
```

## 多重继承

Python 支持多重继承，即一个类可以继承多个基类。

```python
class Base1:
    def method(self):
        return 'Base1 method'

class Base2:
    def method(self):
        return 'Base2 method'

class Child(Base1, Base2):
    pass

c = Child()
print(c.method())  # 输出: Base1 method
```

在多重继承中，如果存在同名方法，Python 会按照从左到右的顺序查找基类中的方法。

### 方法调用解析顺序（MRO）

Python 使用 C3 线性化算法（MRO）来确定基类的方法调用顺序。可以通过类的 `__mro__` 属性或 `mro()` 方法查看这个顺序。

```python
print(Child.__mro__)
# 输出: (<class '__main__.Child'>, <class '__main__.Base1'>, <class '__main__.Base2'>, <class 'object'>)
```

## 抽象基类

在 Python 中，我们可以通过 `abc` 模块定义抽象基类，这样就可以定义一些方法，强制要求子类实现这些方法。

```python
from abc import ABC, abstractmethod

class Animal(ABC):
    @abstractmethod
    def speak(self):
        pass

class Dog(Animal):
    def speak(self):
        return "Woof!"

# a = Animal()  # TypeError: Can't instantiate abstract class Animal with abstract methods speak
d = Dog()
print(d.speak())  # 输出: Woof!
```

在这个例子中，`Animal` 是一个抽象基类，它要求任何继承自 `Animal` 的子类必须实现 `speak` 方法。

### 总结

类继承允许我们构建层次化的类结构，有效地重用代码，同时提供了扩展现有功能的能力。理解继承和相关概念（如多重继承、方法重写、抽象基类等）对于编写高质量的 Python 代码非常重要。