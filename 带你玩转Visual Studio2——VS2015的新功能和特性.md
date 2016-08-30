之前写了一系列《[带你玩转Visual Studio](http://blog.csdn.net/column/details/visualstudio.html)》的文章，有一段时间没有更新这一系列了。

由于项目的需要，工作中的开发环境由VS2010升级至VS2015，现在就说说VS2015相对于VS2010有哪些新特性吧。本系列后续的文章若未特殊说明，均是在VS2015开发环境下进行的。本人安装的版本是Microsoft Visual Studio Enterprise 2015 (Version 14.0.25123.00) Update2.
***

#更换主题颜色
用户可根据自己的喜好选择不同的主题颜色：
Tools->Options...->Environment->General->Visual experience->Color theme.
好像VS2012开始就有主题的选择，这有多种主题可供我们选择，有经典的蓝色(Blue)、通用的亮色(Light)和装逼范的黑色(Dark).
<center><img alt="蓝色(Blue)" src="http://img.blog.csdn.net/20160515184208118" width="90%" />
蓝色(Blue)</center>
<center><img alt="亮色(Light)" src="http://img.blog.csdn.net/20160515184325431" width="90%" />
亮色(Light)</center>
<center><img alt="黑色(Dark)" src="http://img.blog.csdn.net/20160515184415494" width="90%" />
黑色(Dark)</center>


你可以根据自己的喜好选择不同的主题，如果这些主题中都没有你想要的，还可以通过下载主题插件([ Visual Studio 2012 Color Theme Editor](https://visualstudiogallery.msdn.microsoft.com/366ad100-0003-4c9a-81a8-337d4e7ace05))提供更多的主题给你选择。
***

#代码智能提示
可对关键字、已有对象(变量、方法或类)等进行智能的提示。
<center>
![代码智能提示](http://img.blog.csdn.net/20160515190424111)
代码智能提示</center>
***

#自定义窗口布局
你是否曾经遇到过“因为一个意外的操作而整个窗口布局混乱”的情况，需要费好大的功能才能调整回去。VS2015就为我们解决了这个问题，我们可以根据自己的习惯自定义窗口布局，并保存(备份)这些布局。当窗口因某个失误的操作混乱时，我们可以切换回已保存的布局。

- 保存设置好的布局：Windows->Save Windows Layout
- 应用已保存的布局：Windows->Apply Windows Layout
- 管理窗口布局项 ：Windows->Manage Windows Layout
<center>![自定义窗口布局](http://img.blog.csdn.net/20160515203529655)
自定义窗口布局</center>

有这个功能，我们可以定义多个布局。如在工作中在Windows下进行开发，定义一个方便操作的布局；在家或出差时用Surface Pro看代码，定义一个方面阅读的布局。

#诊断工具
VS2015有一个非常强大的功能，就是诊断工具(Diagnotic Tools)，它能在调试时及时也监控CPU、内存的变化。这个功能可以方便地帮助我们在调试的过程及时地跟踪程序的性能。如下图
<center>![诊断工具](http://img.blog.csdn.net/20160521121955455)
诊断工具</center>

默认在Debuging调试时就会出现这个视图，如果没有可以通过Debug->Show Diagnotic Tools打开这个视图。

如果你不需要这个功能，也可以通过Tools->Options->Debugging->General->Enable Diagnotic Tools while Debugging禁用该功能。

#支持C++11
VS2015完全支持C++11标准，对C++14的支持已经基本完成，并支持部分C++17标准。
***

#支持Git和Github
VS2013开始就已经Git进行代码版本管理，在VS2015的完整安装包中已经包含了Git和Github拓展的程序。关于Git的应该可以参考：
[http://www.cnblogs.com/yunfeifei/p/4207093.html](http://www.cnblogs.com/yunfeifei/p/4207093.html)
***
***

上一篇回顾： 
[带你玩转Visual Studio——命令行编译C/C++程序](http://blog.csdn.net/luoweifu/article/details/49847749)

下一篇要讲述的内容： 
带你玩转Visual Studio——VC++的多线程开发
***
