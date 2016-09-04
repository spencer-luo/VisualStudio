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
#define _API_ _declspec( dllexport )
#else
#define _API_ _declspec(dllimport)
#endif
#define EAPI extern "C" _API_
```

这段代码简单解释一下，如果定义了DYNAMIC_EXPORT宏，则_API_表示导出接口，否则表示导入接口；而  #define EAPI extern "C" _API_  表示以C的方式导出(导入)接口。我们在这三个工程中都加入DYNAMIC_EXPORT预编译宏，表示导出接口；而在使用这三个工程(库)的工程(如VisualStudio)中不加VisualStudio宏，表示导入接口。


将这三个工程编译成动态库dll,并用VS的”dumpbin /exports ProjectName.dll”命令查看这三个dll的接口如下：
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

## C++编译函数修饰


# 编译动态库

#总结
这里主要总结一下_cdecl、_stdcall、__fastcall三者之间的区别：

 |要点|\__cdecl|\__stdcall|\__fastcall|
|---|---|---|---|
|参数传递方式|右->左 |右->左 |左边开始的两个不大于4字节（DWORD）的参数分别放在ECX和EDX寄存器，其余的参数自右向左压栈传送|
|清理栈方|调用者清理|被调用函数清理|被调用函数清理|
|适用场合|C/C++、MFC的默认方式; 可变参数的时候使用;|Win API|要求速度快|
|C编译修饰约定|_functionname|_functionname@number|@functionname@number|


上一篇回顾： 
[带你玩转Visual Studio——绑定进程调试](http://blog.csdn.net/luoweifu/article/details/51570947)

下一篇要讲述的内容： 
带你玩转Visual Studio——调用约定与(动态)库

***