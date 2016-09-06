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
	X--void ， 
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
## 编译并使用动态库

要使编译出的动态库更有通过性，我们一般会用C的方式来进行进行编译，即使用
 
	extern "C" __declspec(dllexport)

进行导出接口的声明。


我们使用C的编译方式来编译这三个工程，得到CdeclProject.dll、StdcallProject.dll、FastcallProject.dll三个动态库，现在我们可以在VisualStudio工程(这是生成目标为.exe的工程)中使用他们：
```Cpp
#include "Cdecl.h"
#include "Stdcall.h"
#include "FastCall.h"

int main()
{
	int r1 = add(10, 5);
	int r2 = sub(10, 5);
	double r3 = multi(10.0, 5.0);
	return 0;
}

```

编译VisualStudio，会发现报以下两个错误：
>error LNK2019: unresolved external symbol __imp__sub referenced in function _main
>error LNK2019: unresolved external symbol __imp__multi referenced in function _main

这是因为VisualStudio工程默认是使用__cdecl约定，使用到sub和multi的时候,会去找_sub(或sub)、_multi(或multi)的函数名。但sub是__stdcall约定，编译出的StdcallProject.dll中的名称是_sub@8；而multi是__fastcall约定，编译出的FastcallProject.dll中名称是@multi@16。所以自然就找不到。

同理，我们将VisualStudio工程的默认调用约定改成__stdcall，再进行编译，会报以下两个错误：
>error LNK2019: unresolved external symbol __imp__add@8 referenced in function _main
>error LNK2019: unresolved external symbol __imp__multi@16 referenced in function _main

把VisualStudio工程的默认调用约定改成__fastcall，再进行编译，会报以下两个错误：
>error LNK2019: unresolved external symbol __imp_@add@8 referenced in function _main
>error LNK2019: unresolved external symbol __imp_@sub@8 referenced in function _main

相信你一定明白怎么回事了，我就不再解释了。由此可见


**【要点一】：如果一个解决方案中有多个工程,或一个工程中使用了多个开源库，所有工程最好使用同一种默认调用约定。**

## 显示使用调用约定
如果我要使编译出的dll在不同的调用约定下都能正常使用，可以这样实现：

**【要点二】：要使编译出的动态库在不同的调用约定下都能使用，需要对所有要导出的函数使用显示的调用约定**

```
EAPI int __cdecl add(int a, int b);

int __cdecl add(int a, int b)
{
	return a + b;
}
```

```Cpp
EAPI int __stdcall sub(int a, int b);

EAPI int __stdcall sub(int a, int b)
{
	return a - b;
}
```

```Cpp
EAPI double __fastcall multi(double a, double b);

double __fastcall multi(double a, double b)
{
	return a * b;
}
```

这时，VisualStudio工程的默认调用约定不管是用__cdecl、__stdcall还是__fastcall，都能正常编译和运行。


## 使用导出模块文件
上面显示使用调用约定的方式虽然可以使编译出的dll在任何调用约定下都能被使用，但仅限于在相同的编译器下。

我们用”dumpbin /exports ProjectName.dll”命令查看这三个dll的导出接口：

	add = @ILT+215(_add)
	_sub@8 = @ILT+225(_sub@8)
	@multi@16 = @ILT+335(@multi@16)

你会发现这和我们第一次查看的结果一样，但你仔细看一下第一条结果和后面两个有点不样。第一条结果左边(add)和右边名称不一样(_add),后面两条结果左边和右边名称都相同。这是因为:

>通过关键字extern "C" __declspec(dllexport)声明的接口函数可以保证__cdecl调用约定的函数名称不被改变(不被编译器添加特殊的符号进行修饰)，却不能保证__stdcall和__fastcall调用约定的函数不被改变。

要命__stdcall和__fastcall调用约定的函数不被改变，我们需要使用模块文件。为CdeclProject、FastcallProject和StdcallProject三个工程添加模块文件，右键工程 -> Add -> New Item -> Visual C++ -> Code -> Module-Definition File(.def)

```
LIBRARY     "CdeclProject"	;Library name
EXPORTS
add @ 1 ;Export the add function
```

```
LIBRARY     "StdcallProject"	;Library name
EXPORTS
sub @ 1 ;Export the sub function
```

```
LIBRARY     "FastcallProject"	;Library name
EXPORTS
multi @ 1 ;Export the multi function
```

对这三个工程进行编译，再用”dumpbin /exports ProjectName.dll”命令查看导出接口如下：

	add = @ILT+290(_add)
	sub = @ILT+590(_sub@8)
	multi = @ILT+435(@multi@16)

你会看到这三个名称的函数都没被更改了，这时编译出来的dll才具有跨平台、跨编译器的通用性。

**【要点三】:要使编译出的动态库具有跨平台、跨编译器的通用性，需要使用模块文件定义导出接口(__cdecl调用约定除外)。**



上一篇回顾： 
[带你玩转Visual Studio——调用约定__cdecl、__stdcall和__fastcall](http://blog.csdn.net/luoweifu/article/details/52425733)

下一篇要讲述的内容： 
带你玩转Visual Studio2——Git与Github的使用

***
***