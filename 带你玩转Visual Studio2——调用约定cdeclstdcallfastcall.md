#带你玩转Visual Studio2——调用约定__cdecl、__stdcall和__fastcall

有一定C++开发经验的人一定对"\__cdecl、\__stdcall、__fastcall"肯定不陌生吧！但你真正理解了吗？是的，我曾在这采了无数个坑，栽了无数个跟头，终于忍无可忍要把它总结一下(虽然我已经有能力解决大部分这种问题了)!


#什么是调用约定
>函数的**调用约定**，顾名思义就是对函数调用的一个约束和规定(规范)，描述了函数参数是怎么传递和由谁清除堆栈的。它决定以下内容：(1)函数参数的压栈顺序，(2)由调用者还是被调用者把参数弹出栈，(3)以及产生函数修饰名的方法。

我们知道函数由以下几部分构成:返回值类型 函数名(参数列表)，如:
【code1】

	void function();
	int add(int a, int b);

以上是大家所熟知的构成部分，其实函数的构成还有一部分，那就是调用约定。如下：
【code2】

	void __cdecl function();
	int __stdcall add(int a, int b);

上面的\__cdecl和\__stdcall就是调用约定，其中\__cdecl是C和C++默认的调用约定，所以通常我们的代码都如 【code1】中那样定义，编译器默认会为我们使用\__cdecl调用约定。常见的调用约定有\__cdecl、\__stdcall、fastcall，应用最广泛的是\__cdecl和\__stdcall,下面我们会详细进行讲述。。还有一些不常见的，如 \__pascal、\__thiscall、\__vectorcall。


##声明和定义处调用约定必须要相同
在VC++中，调用约定是函数类型的一部分，**因此函数的声明和定义处调用约定要相同，不能只在声明处有调用约定，而定义处没有或与声明不同。**如下：
【code3】 错误的使用一：

	int __stdcall add(int a, int b);
	int add(int a, int b)
	{
		return a + b;
	}

报错：
>error C2373: 'add': redefinition; different type modifiers
>error C2440: 'initializing': cannot convert from 'int (__stdcall *)(int,int)' to 'int'


【code4】 错误的使用二：

	int  add(int a, int b);
	int __stdcall add(int a, int b)
	{
		return a + b;
	}

报错：
>error C2373: 'add': redefinition; different type modifiers
error C2440: 'initializing': cannot convert from 'int (__cdecl *)(int,int)' to 'int'

【code5】 错误的使用三：

	int __stdcall add(int a, int b);
	int __cdecl add(int a, int b)
	{
		return a + b;
	}

报错：
>error C2373: 'add': redefinition; different type modifiers
error C2440: 'initializing': cannot convert from 'int (__stdcall *)(int,int)' to 'int'

【code6】 正确的用法：

	int __stdcall add(int a, int b);
	int __stdcall add(int a, int b)
	{
		return a + b;
	}

##函数的调用过程
要深入理解函数调用约定，你须要了解函数的调用过程和调用细节。
假设函数A调用函数B，我们称A函数为"调用者",B函数为“被调用者”。如下面的代码，ShowResult为调用者，add为被调用者。

	int add(int a, int b)
	{
		return a + b;
	}
	
	void ShowResult()
	{
		std::cout << add(5, 10) << std::endl;
	}

函数调用过程可以这么描述：
（1）先将调用者（A）的堆栈的基址（ebp）入栈，以保存之前任务的信息。
（2）然后将调用者（A）的栈顶指针（esp）的值赋给ebp，作为新的基址（即被调用者B的栈底）。
（3）然后在这个基址（被调用者B的栈底）上开辟（一般用sub指令）相应的空间用作被调用者B的栈空间。
（4）函数B返回后，从当前栈帧的ebp即恢复为调用者A的栈顶（esp），使栈顶恢复函数B被调用前的位置；然后调用者A再从恢复后的栈顶可弹出之前的ebp值（可以这么做是因为这个值在函数调用前一步被压入堆栈）。这样，ebp和esp就都恢复了调用函数B前的位置，也就是栈恢复函数B调用前的状态。
这个过程在AT&T汇编中通过两条指令完成，即：
![](http://sunlogging.com/wp-content/uploads/2016/09/function.jpg)

       leave
       ret
      这两条指令更直白点就相当于：
      mov   %ebp , %esp
      pop    %ebp

此部分内容参考：[http://blog.csdn.net/zsy2020314/article/details/9429707](http://blog.csdn.net/zsy2020314/article/details/9429707)

#__cdecl的特点
__cdecl 是 C Declaration  的缩写，表示 C 和 C++ 默认的函数调用约定。是C/C++和MFCX的默认调用约定。

- 按从右至左的顺序压参数入栈、。
- 由调用者把参数弹出栈。切记：对于传送参数的内存栈是由调用者来维护的，返回值在EAX中。因此对于像printf这样可变参数的函数必须用这种约定。
- 编译器在编译的时候对这种调用规则的函数生成修饰名的时候，在输出函数名前加上一个下划线前缀，格式为_function。如函数int add(int a, int b)的修饰名是_add。


(1).为了验证参数是从右至左的顺序压栈的，我们可以看下面这段代码，Debug进行单步调试,可以看到我们的调用栈会先进入GetC()，再进入GetB()，最后进入GetA()。
![](http://sunlogging.com/wp-content/uploads/2016/09/cdecl.jpg)

(2).第二点“调用者把参数弹出栈”，这是编译器的工作，暂时没办法验证。要深入了解这部分，需要学习汇编语言相关的知识。

(3).函数的修饰名，这个可以通过对编译出的dll使用VS的"dumpbin /exports *ProjectName*.dll"命令进行查看(后面章节会进行详细介绍)，或直接打开.obj文件查找对应的方法名(如搜索add)。

从代码和程序调试的层面考虑，参数的压栈顺序和栈的清理我们都不用太观注，因为这是编译器的决定的，我们改变不了。但第三点却常常困扰我们，因为如果不弄清楚这点，在多个库之间(如dll、lib、exe)相互调用、依赖时常常出出现莫名其妙的错误。这个我在后面章节会进行详细介绍。


#__stdcall的特点
\_\_stdcall是Standard Call的缩写，是C++的标准调用方式,当然这是微软定义的标准，\_\_stdcall通常用于Win32 API中(可查看WINAPI的定义)。

- 按从右至左的顺序压参数入栈。
- 由被调用者把参数弹出栈。切记：函数自己在退出时清空堆栈，返回值在EAX中。
- \_\_stdcall调用约定在输出函数名前加上一个下划线前缀，后面加上一个“@”符号和其参数的字节数，格式为\_function@number。如函数int sub(int a, int b)的修饰名是_sub@8。

#__fastcall的特点
\_\_fastcall调用的主要特点就是快，因为它是通过寄存器来传送参数的。

- 实际上\_\_fastcall用ECX和EDX传送前两个DWORD或更小的参数，剩下的参数仍自右向左压栈传送，被调用的函数在返回前清理传送参数的内存栈。
- \_\_fastcall调用约定在输出函数名前加上一个“@”符号，后面也是一个“@”符号和其参数的字节数，格式为@function@number,如double  multi(double a, double b)的修饰名是@multi@16。
- \_\_fastcall和\_\_stdcall很象，唯一差别就是头两个参数通过寄存器传送。注意通过寄存器传送的两个参数是从左向右的，即第1个参数进ECX，第2个进EDX，其他参数是从右向左的入栈，返回仍然通过EAX。

以上内容参考：[http://www.3scard.com/index.php?m=blog&f=view&id=10](http://www.3scard.com/index.php?m=blog&f=view&id=10)

#__thiscall
\__thiscall是C++类成员函数缺省的调用约定，但它没有显示的声明形式。因为在C++类中，成员函数调用还有一个this指针参数，因此必须特殊处理，thiscall调用约定的特点：

- 参数入栈：参数从右向左入栈
- this指针入栈：如果参数个数确定，this指针通过ecx传递给被调用者；如果参数个数不确定，this指针在所有参数压栈后被压入栈。
- 栈恢复：对参数个数不定的，调用者清理栈，否则函数自己清理栈。


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
- 