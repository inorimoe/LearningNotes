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
