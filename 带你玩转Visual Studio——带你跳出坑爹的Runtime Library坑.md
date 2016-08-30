上一篇文章[带你玩转Visual Studio——带你理解微软的预编译头技术](http://blog.csdn.net/luoweifu/article/details/49010627)我们了解了微软的预编译头技术，预编译的方式让我们的工程编译的更加快速；本篇文章将继续介绍微软的另一项技术，也就是运行时库Runtime Library。
***

在Windows下进行C++的开发，不可避免的要与Windows的底层库进行交互，然而VS下的一项设置MT、MTd、MD和MDd却经常让人搞迷糊，相信不少人都被他坑过，特别是你工程使用了很多第三库的时候，及容易出现各种链接问题。看一下下面这个错误提示：
	LIBCMT.lib(_file.obj) : error LNK2005: ___initstdio already defined in libc.lib(_file.obj)
	LIBCMT.lib(_file.obj) : error LNK2005: ___endstdio already defined in libc.lib(_file.obj)

有多少人被这玩意坑过，被坑过的请举脚！哈哈……

既然这里这么容易出问题，我们就有必要对其进行深入的了解，**知其然且知其所以然才能万事无惧！**

#1. 什么是Runtime Library？
Runtime Library就是运行时库，也简称CRT(C Run Time Library)。是程序在运行时所需要的库文件，通常运行时库是以Lib或Dll形式提供的。

Windows下**C Runtime Library**是微软对C标准库函数的实现，这样每个程序可以直接使用C标准库的函数；后来出现了C++，于是又在C Runtime Library基础上开发了**C++ Runtime Library**，实现了对C++标准库的支持。因此现在Windows下的C/C++运行时库既包含子C标准库，也包含了C++标准库。如果你安装了VS2010，在安装目录下的VC\crt\src下(如我的目录是C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\crt\src)有运行时库(CRT)的源代码，这里既有C的文件(如output.c、stdio.h等)，也有C++的文件(如iostream、string)。

在C Runtime Library出现之前，许多程序都使用C编写，而这些程序都要使用标准的C库，按照以前的方式每一个程序最终都要拷贝一份标准库的实现到程序中，这样同一时刻内存中可能有许多份标准库的代码（一个程序一份），所以微软出于效率的考虑把标准C库做为动态链接来实现，这样多个程序使用C标准库时内存中就只有一份拷贝了。

确切地说运行时库指的就是对这些底层的基础功能实现的动态库(Dll),运行时库和普通的Dll一样，只有程序用到了它才会被加载，没有程序使用的时候不会驻留内存的。话虽如此，但有多少系统的东西说不定也是用C写的，这些东西的存在就使C运行时库存在于内存中了，所以运行时库几乎总是需要的。虽然说运行时库应该是动态库，但习惯上我们把与动态运行时库相同代码编译出来的静态库也称为运行时库，因此VC++下的运行时库有ML、MLd、MT、MTd、MD、MD六种(这个后面会讲)。


##1.1 运行时库的主要作用
1. 提供C标准库(如memcpy、printf、malloc等)、C++标准库（STL）的支持。

2. 应用程序添加启动函数，启动函数的主要功能为将要进行的程序初始化，对全局变量进行赋初值，加载用户程序的入口函数。

不采用宽字符集的控制台程序的入口点为mainCRTStartup(void)。下面我们以该函数为例来分析运行时库究竟为我们添加了怎样的入口程序。这个函数在crt0.c中被定义，下列的代码经过了笔者的整理和简化：

```
void mainCRTStartup(void)
{
　int mainret;
　/*获得WIN32完整的版本信息*/
　_osver = GetVersion();
　_winminor = (_osver >> 8) & 0x00FF ;
　_winmajor = _osver & 0x00FF ;
　_winver = (_winmajor << 8) + _winminor;
　_osver = (_osver >> 16) & 0x00FFFF ;
　_ioinit(); /* initialize lowio */
　/* 获得命令行信息 */
　_acmdln = (char *) GetCommandLineA();
　/* 获得环境信息 */
　_aenvptr = (char *) __crtGetEnvironmentStringsA();
　_setargv(); /* 设置命令行参数 */
　_setenvp(); /* 设置环境参数 */
　_cinit(); /* C数据初始化：全局变量初始化，就在这里！*/
　__initenv = _environ;
　mainret = main( __argc, __argv, _environ ); /*调用main函数*/
　exit( mainret );
}
```
从以上代码可知，运行库在调用用户程序的main或WinMain函数之前，进行了一些初始化工作。初始化完成后，接着才调用了我们编写的main或WinMain函数。只有这样，我们的C语言运行时库和应用程序才能正常地工作起来。

除了crt0.c外，C运行时库中还包含wcrt0.c、 wincrt0.c、wwincrt0.c三个文件用来提供初始化函数。wcrt0.c是crt0.c的宽字符集版，wincrt0.c中包含 windows应用程序的入口函数，而wwincrt0.c则是wincrt0.c的宽字符集版。
***
***

#2. MT、MTd、MD、MDd、(ML、MLd 已废弃)的区别与原理
我们可以在Properties->Configuration Properties->C/C++->Code Generation->Runtime Library中设置采用的运行时库的类型。
<center>![Runtime Library](http://img.blog.csdn.net/20151011224714929)
Runtime Library</center>

在[带你玩转Visual Studio——带你发布自己的工程库](http://blog.csdn.net/luoweifu/article/details/48895765)一文中已经详细讲解了静态库(Lib)与动态库(Dll)的区别。我们知道编译出的静态库只有一个ProjectName.lib文件，而编译出的动态库有两个文件：ProjectName.lib+ProjectName.dll，一个是导入库，一个动态库。

**VC++中有六种Runtime Library的类型:**
|类型|简称|含义|对应的库名称|备注|
|-----|---|---|---|
|Single-Threaded|/ML|Release版的单线程静态库|libc.lib|<font color="0080ff">VS2003以后被废弃</font>|
|Single-Threaded Debug|/MLd|Debug版的单线程静态库|libcd.lib|<font color="0080ff">VS2003以后被废弃</font>|
|Multi-threaded|/MT|Release版的多线程静态库|libcmt.lib||
|Multi-threaded Debug|/MTd|Debug版的多线程静态库|libcmtd.lib||
|Multi-threaded DLL|/MD|Release版的多线程动态库|msvcrt.lib+msvcrtxx.dll||
|Multi-threaded DLL Debug |MDd|Debug版的多线程动态库|msvcrtd.lib+msvcrtxxd.dll||

你可以在VS的安装目录下找到这些库文件，如我的VS2010安装在C:\Program Files (x86)\Microsoft Visual Studio 10.0，则可以在C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\lib\和C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\lib\amd64\中分别找到对应32位和64位的libcmt.lib、libcmtd.lib、msvcrt.lib、msvcrtd.lib库。libc.lib和libcd.lib由于在VS2005就已经废弃了，所以在这肯定找不到。

通过上面的表格你会发现，多线程的动态运行时库是|msvcrt.lib+msvcrtxx.dll，之所以是msvcrtxx.dll是因为每一个版本的VS使用的库名称还不一样。而且还不止包含一个库，除了主要的MSVCRT库外，还有MSVCPRT、MSVCIRT库。它们之间的对应关系如下：
|导入库|MSVCRT.LIB|MSVCRTD.LIB|MSVCPRT.LIB|MSVCPRTD.LIB|MSVCIRT.LIB|MSVCIRTD.LIB|
|---|---|---|---|---|---|---|
|Visual C++ 5.0|MSVCRT.DLL|MSVCRTD.DLL|MSVCP5.DLL|MSVCP5D.DLL|MSVCIRT.DLL|MSVCIRTD.DLL|
|Visual C++ 6.0|MSVCRT.DLL|MSVCRTD.DLL|MSVCP6.DLL|MSVCP6D.DLL|MSVCIRT.DLL|MSVCIRTD.DLL|
|Visual C++ .NET 2002|MSVCR70.DLL|MSVCR70D.DLL|MSVCP70.DLL|MSVCP70D.DLL| | |
|Visual C++ .NET 2003|MSVCR71.DLL|MSVCR71D.DLL|MSVCP71.DLL|MSVCP71D.DLL| | |
|Visual C++ 2005|MSVCR80.DLL|MSVCR80D.DLL|MSVCP80.DLL|MSVCP80D.DLL| | |
|Visual C++ 2008|MSVCR90.DLL|MSVCR90.DLL|MSVCP90.DLL|MSVCP90D.DLL| | |
|Visual C++ 2010|MSVCR100.DLL|MSVCR100D.DLL|MSVCP100.DLL|MSVCP100D.DLL| | |
参考阅读：[https://support.microsoft.com/en-us/kb/154753](https://support.microsoft.com/en-us/kb/154753)

在你的VS安装目录下(如C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\redist\x64\Microsoft.VC100.CRT)，及系统目录C:\Windows\System32、C:\Windows\SysWOW64下都能找到对应的.dll库。

很多的软件在发布自己的产品时也都会带上这些DLL(防止用户的操作系统没有安装VS，或在系统目录下找不到对应的DLL)，如我电脑上的百度影音安装目录下就有MSVCR71.DLL(C:\Program Files (x86)\baidu\BaiduPlayer\4.1.2.286\MSVCR71.DLL)，WPS的安装目录下有msvcr100.dll(C:\Program Files (x86)\WPS Office\9.1.0.5132\wtoolex\msvcr100.dll)和msvcp100.dll(C:\Program Files (x86)\WPS Office\9.1.0.5132\wtoolex\msvcp100.dll)


(1). 静态链接的单线程库
静态链接的单线程库只能用于单线程的应用程序， C 运行时库的目标代码最终被编译在应用程序的二进制文件中。通过 /ML 编译选项可以设置 Visual C++ 使用静态链接的单线
程库。
(2). 静态链接的多线程库
静态链接的多线程库的目标代码也最终被编译在应用程序的二进制文件中，但是它可以在多线程程序中使用。通过 /MT 编译选项可以设置 Visual C++ 使用静态链接的多线程库。
该选项生成的可执行文件运行时不需要运行时库dll的参加，会获得轻微的性能提升，但最终生成的二进制代码因链入庞大的运行时库实现而变得非常臃肿。当某项目以静态链接库的形式嵌入到多个项目，则可能造成运行时库的内存管理有多份，最终将导致致命的“Invalid Address specified to RtlValidateHeap”问题。
(3). 动态链接的运行时库
动态链接的运行时库将所有的 C 库函数保存在一个单独的动态链接库 MSVCRTxx.DLL 中， MSVCRTxx.DLL 处理了多线程问题。使用 /MD 编译选项可以设置 Visual C++ 使用动态。
链接时将按照传统VC链接dll的方式将运行时库MSVCRxx.DLL的导入库MSVCRT.lib链接，在运行时要求安装了相应版本的VC运行时库可再发行组件包（当然把这些运行时库dll放在应用程序目录下也是可以的）。 因/MD和/MDd方式不会将运行时库链接到可执行文件内部，可有效减少可执行文件尺寸。当多项目以MD方式运作时，其内部会采用同一个堆，内存管理将被简化，跨模块内存管理问题也能得到缓解。

/MDd 、 /MLd 或 /MTd 选项使用 Debug runtime library( 调试版本的运行时刻函数库 ) ，与 /MD 、 /ML 或 /MT 分别对应。 Debug 版本的 Runtime Library 包含了调试信息，并采用了一些保护机制以帮助发现错误，加强了对错误的检测，因此在运行性能方面比不上 Release 版本。 

**结论：/MD和/MDd将是潮流所趋，/ML和/MLd方式请及时放弃，/MT和/MTd在非必要时最好也不要采用了。**
***
***

#3. 如何避免这种错误
3.1. **/MD和/MDd将是潮流所趋,/ML和/MLd方式请及时放弃,/MT和/MTd在非必要时最好也不要采用了。**尽量使用/MD、/MDd这种方式，除非有某些特殊的需要,如希望编译出来的.exe可执行文件不需要依赖运行时库的.dll；
2. **在多工程开发时，所有的工程使用同一种运行时库。**如Utils的Solution下有两个Project：Utils和UsingUtils，UsingUtils工程要使用Utils工程编译出来的库。如果Utils使用了/MDd的方式，UsingUtils也要使用/MDd的方式，否则会报链接错误。
如果Utils使用MTd的方式，而UsingUtils使用/MDd的方式，则会出现重定义的错误，如：

	1>LIBCMTD.lib(setlocal.obj) : error LNK2005: __configthreadlocale already defined in MSVCRTD.lib(MSVCR100D.dll)
	1>LIBCMTD.lib(dbgheap.obj) : error LNK2005: __free_dbg already defined in MSVCRTD.lib(MSVCR100D.dll)
	1>LIBCMTD.lib(dbgheap.obj) : error LNK2005: __CrtSetCheckCount already defined in MSVCRTD.lib(MSVCR100D.dll)
这是因为Utils使用MTd的方式，包含了libcmtd.lib库；而UsingUtils使用/MDd的方式，要包含msvcrtd.lib+msvcrtxxd.dll。libcmtd.lib和msvcrtd.lib是用相同代码编译的，一个是静态库，一个动态库的导入库，同时包含libcmtd.lib和msvcrtd.lib肯定就对相同的函数进行了重复的定义。

3. **以Release方式进行编译时使用Release的库，使用Debug的方式编译时使用Debug的库。**如编译Release版本的UsingUtils时，要使用Release方式编译出来的Utils库，编译Debug版本的UsingUtils时，要使用Debug方式编译出来的库。
***
***

#4. 历史发展的角度讲解运行时库
##4.1 从操作系统的角度出发
我们知道操作系统一般是用C写的(因为那时还没有C++，C已经算是最高级的计算机语言了)，不管是Linux/Unix还是Windows底层都是大量的C代码。在开发操作系统及相应的应用程序时，很多的程序都会用到相同基础功能的函数库。为了方便开发就把经常用到的底层的基础函数封闭成库(不然你每写一个程序都要把这基础功能实现的源代码拷贝一份到自己的工程，或自己再实现一次)，于是就有了**C运行时库(C Runtime Library)**，也就是静态库libc.lib(Release版)、libcd.lib(Debug版)。

因为早期的操作系统和程序都相应简单，用户的需求也不高，那时的操作系统还没有多任务、多线程的概念。所以libc.lib、libcd.lib当然只能支持单线程的程序，而无法支持多线程的程序，因此这个运行时库叫Single-Threaded(/ML)的方式。

后来，随着计算机的普及和发展，计算机要完成的任务越来越多，人们对时间和性能的要求也越来越高，为满足这些需求，操作系统就有了多任务的概念，也有了多线程的技术。而之前的运行时库libc.lib、libcd.lib只能用于单线程，已经无法满足很多程序的需要，于是多线程的运行时库也就应运而生，这就是libcmt.lib、libcmtd.lib，也就是/MT、/MTd的方式。

/MT、/MTd解决了多线程的问题，但随着程序的越来越复杂，一个程序可能会用到多个其他程序的库，多个程序可能会用到相同的库，在内存中会保存多份的相同的静态库。假设A程序使用了C.lib，B程序也使用了C.lib，A、B程序同时运行时，在内存中就会同时存在两份C.lib。
<center>![静态库在内存中的呈现方式](http://img.blog.csdn.net/20151013000655609)
静态库在内存中的呈现方式</center>
为了解决这个问题，就产生了动态库的技术。于是就有了动态的运行时库Multi-threaded DLL(/MD)、Multi-threaded DLL Debug(/MDd)。多个程序使用同一个动态库，在内存中只会有一份，效果图如下
<center>![动态库在内存中的呈现方式](http://img.blog.csdn.net/20151013001738525)
动态库在内存中的呈现方式</center>


##4.2 从语言的角度
我们都知道，先有了C语言，后来才在C的基础上发展出了C++语言，而C++又对C兼容，相当是C的一个超集。
一开始的运行时库，只是C的运行时库(C Runtime Library)，包含了对C标准函数的实现。后来随着C++的产生，又把C++程序运行时要用的底层基础库加了进去，就有了C/C++的运行时库(C/C++ Runtime Library)，这时的运行时库既包含了标准C函数的实现，也包含了C++ STL的实现。
***
***

上一篇回顾： 
[带你玩转Visual Studio——带你理解微软的预编译头技术](http://blog.csdn.net/luoweifu/article/details/49010627)

下一篇要讲述的内容： 
带你玩转Visual Studio——带你理解多字节编码与Unicode码
***

**(本文未完，明日继续)**


