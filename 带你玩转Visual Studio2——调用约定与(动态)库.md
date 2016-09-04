# 带你玩转Visual Studio——调用约定与(动态)库

上一篇文章[带你玩转Visual Studio——调用约定\_\_cdecl、\_\_stdcall和\_\_fastcall](http://blog.csdn.net/luoweifu/article/details/52425733)中已经讲述了\_\_cdecl、\_\_stdcall和\_\_fastcall几种调用约定的主要区别。这一章将进一步深入了解不同调用约定对编译后函数修饰名的影响，及调用约定对库函数的影响。

# VS设置默认的调用约定
上一章已经讲了，C/C++默认的调用约定是\_\_cdecl，那能不能修改这个默认的调用约定呢？
答案是肯定的。假设你有一个工程名叫VisualStudio，你想让这个工程下的所有函数默认都使用\_\_stdcall，右键工程->Properties->Configuration Properties->C/C++->Advanced->Calling Convention,将其设置为\_\_stdcall即可。
![设置默认的调用约定](http://sunlogging.com/wp-content/uploads/2016/09/callingconvention.jpg)

**说明：**这个值默认是空，因为默认就是\_\_cdecl，当设置为\_\_stdcal，表示这个工程下的所有函数默认使用\_\_stdcall约定，除非在函数中进行了显示声明。设置为其它值含义与此类似。


# 不同调用约定编译后的函数修饰名
上一章提到的几种不同调用约定对编译后函数名的修饰规则，只是指C的编译方式。VS中有两种编译方式，一种是C的编译方式，一种是C++的编译方式。*.c默认使用C的编译方式，而*.cpp文件默认使用C++的编译方式。C和C++对函数名的修饰规则是不同的。

## C编译函数修饰
C编译方式对函数名的修饰规则在上一章已经讲了，再来回顾一下：
|要点|\_\_cdecl|\_\_stdcall|\_\_fastcall|
|---|---|---|---|
|C编译修饰约定|_functionname|_functionname@number|@functionname@number|

为了说明这一点，我们做一个验证。建三个工程分别对应\_\_cdecl、\_\_stdcall和\_\_fastcall，即为这三个工程分别设置默认\_\_cdecl、\_\_stdcall和\_\_fastcall调用约定。
![\_\_cdecl、\_\_stdcall和\_\_fastcall三个工程](http://sunlogging.com/wp-content/uploads/2016/09/project.jpg)

三个工程分别定义三个函数如下：

Cdecl.h
```Cpp
	EAPI int add(int a, int b);
```

Stdcall.h
```Cpp
	EAPI int sub(int a, int b);
```

FastCall.h
```Cpp
	EAPI double multi(double a, double b);
```

其中EAPI的定义如下：
【code1】:
```Cpp
#ifdef DYNAMIC_EXPORT
#define _API_ __declspec(dllexport)
#else
#define _API_ __declspec(dllimport)
#endif

#define EAPI extern "C" _API_
```

这段代码简单解释一下，如果定义了DYNAMIC_EXPORT宏，则_API_表示导出接口，否则表示导入接口；而  #define EAPI extern "C" _API_  表示以C的方式导出(导入)接口。我们在这三个工程中都加入DYNAMIC_EXPORT预编译宏，表示导出接口；而在使用这三个工程(库)的工程(如VisualStudio)中不加DYNAMIC_EXPORT宏，表示导入接口。


将这三个工程编译成动态库(dll),并用VS的”dumpbin /exports ProjectName.dll”命令查看这三个dll的接口如下：
```
dumpbin /exports CdeclProject.dll

ordinal hint RVA      name
      1    0 000110DC add = @ILT+215(_add)
```

```   
dumpbin /exports StdcallProject.dll

ordinal hint RVA      name
      1    0 000110E6 _sub@8 = @ILT+225(_sub@8)
```

```
dumpbin /exports FastcallProject.dll

ordinal hint RVA      name
      1    0 00011154 @multi@16 = @ILT+335(@multi@16)
```

我们可以看到括号中的函数修饰名(_add)、(_sub@8)、(@multi@16)遵循上述所说的规则。

## C++编译函数修饰
在C++的编译方式中，为了能实现C++中的函数重载、继承，编译器增加了更多的修饰符号。

- 以“?”标识函数名的开始，后跟函数名。
- 如果是\_\_cdecall调用约定，函数名后面接“@@YA”标识参数表的开始；如果是\_\_stdcall调用约定，函数名后面接“@@YG”标识参数表的开始；如果是\_\_fastcall调用约定，函数名后面接“@@YI”标识参数表的开始。
- 后面再跟参数表，参数表以代号表示(各代号的含义后面说明)，参数表的第一项为该函数的返回值类型，其后依次为参数的数据类型,指针标识在其所指数据类型前；
- 参数表后以“@Z”标识整个名字的结束，如果该函数无参数，则以“Z”标识结束。

### 参数表代号说明
>X--void ， 
D--char， 
E--unsigned char， 
F--short， 
H--int， 
I--unsigned int， 
J--long， 
K--unsigned long， 
M--float， 
N--double， 
_N--bool，
PA--指针， 
.... 

**说明：**
PA表示指针，后面的代号表明指针类型，如果相同类型的指针连续出现，以“0”代替，一个“0”代表一次重复；如EAPI void func3(long* pL, long* pL2, double* pD);修饰名为：?func3@@YGXPAJ0PAN@Z

如果PA表示的是类对象的指针，则PA后接“V+类名+@@”，如
```Cpp
class Node
{
	int val;
};
EAPI int func4(Node* pNode, int* pVal);
```
修饰名为：?func4@@YGHPAVNode@@PAH@Z

### 实例验证
我们把#define EAPI extern "C" _API_中的extern "C"注释掉
```Cpp
	#define EAPI /*extern "C"*/ _API_
```

三个工程中再加入两个函数的声明和定义
```Cpp
EAPI void func();

EAPI int func2(float a, double b, bool c);
```

```Cpp
EAPI void func()
{
	std::cout<< "func()" << std::endl;
}

EAPI int func2(float a, double b, bool c)
{
	return c ? a + b : 0;
}
```


用C++的方式来编译,再用命令查看函数修饰名如下：

```
dumpbin /exports CdeclProject.dll

ordinal hint RVA      name
       1    0 00011280 ?add@@YAHHH@Z = @ILT+635(?add@@YAHHH@Z)
       2    1 000111C2 ?func2@@YAHMN_N@Z = @ILT+445(?func2@@YAHMN_N@Z)
       3    2 00011050 ?func@@YAXXZ = @ILT+75(?func@@YAXXZ)
```

```   
dumpbin /exports StdcallProject.dll

ordinal hint RVA      name
      1    0 000111BD ?func2@@YGHMN_N@Z = @ILT+440(?func2@@YGHMN_N@Z)
      2    1 0001104B ?func@@YGXXZ = @ILT+70(?func@@YGXXZ)
      3    2 0001114A ?sub@@YGHHH@Z = @ILT+325(?sub@@YGHHH@Z)
```

```
dumpbin /exports FastcallProject.dll

ordinal hint RVA      name
      1    0 00011195 ?func2@@YIHMN_N@Z = @ILT+400(?func2@@YIHMN_N@Z)
      2    1 0001104B ?func@@YIXXZ = @ILT+70(?func@@YIXXZ)
      3    2 000111E5 ?multi@@YINNN@Z = @ILT+480(?multi@@YINNN@Z)
```

# 编译动态库

上一篇回顾： 
[带你玩转Visual Studio——绑定进程调试](http://blog.csdn.net/luoweifu/article/details/51570947)

下一篇要讲述的内容： 
带你玩转Visual Studio——调用约定与(动态)库

***