通过上一篇文章[带你玩转Visual Studio——带你多工程开发](http://blog.csdn.net/luoweifu/article/details/48915347)的讲解，我们能够在一个Solution中创建多个Project，统一管理一个项目的多个Project。本篇文章我们将继续讲解微软的预编译头技术。


#不陌生的stdafx.h
还记得[带你玩转Visual Studio——带你新建一个工程](http://blog.csdn.net/luoweifu/article/details/48692267)一文中的图2(参见下图)吗？我们默认勾选了Precompiled header复选框，创建的工程中就自动添加了stdafx.h和stdafx.cpp，**stdafx.h就是预编译头文件**，勾选Precompiled header就表明采用了微软的预编译头技术。
<center>![Application Settings](http://img.blog.csdn.net/20150923220939144)
Application Settings</center>

##打开或关闭预编译方式
右键工程名->Properties->Configuration Properties->C/C++->Precompiled Header,Precompiled Header下拉列表框选择Use(/Yu)表示**打开**(使用)预编译头的方式，选择Not Using Precompiled Headers表示**关闭**预编译头的编译方式。
<center>![预编译头的设置](http://img.blog.csdn.net/20151009234751288)
预编译头的设置</center>

参数说明：
Precompiled Header:是否采用预编译头的方式；
Precompiled Header File:预编译头文件的名称，VS中文件名的大小写不敏感，但最好保持大小写相同。
Precompiled Header Output File:生成的.pch文件我名称，关于.pch文件将再在下面**预编译原理**小节中讲述。

如果是要使用预编译头文件的方式，还需要设置stdafx.cpp文件的属性。右键stdafx.cpp->Properties->Configuration Properties->C/C++->Precompiled Header，Precompiled Header下拉列表框中选择Create(Yc).
<center>![设置.cpp的属性](http://img.blog.csdn.net/20151009235711327)
设置.cpp的属性</center>

##注意事项
**每一个源文件的第一行代码必须包含预编译头文件。**如果你的工程选用了预编译头文件的方式，每一个.cpp文件的第一行代码必须包含预编译头文件(#include "stdafx.h")，否则会编译出错。
***
***

#对编译技术的内存原理
stdafx名称的英文全称为：Standard Application Framework Extensions

***
***

#如何在非MFC工程中使用MFC库
这部分内容之前写过，就不再赘述，直接给出链接：
[非MFC工程中使用MFC库](http://blog.csdn.net/luoweifu/article/details/41527069)
***
***


上一篇回顾： 
[带你玩转Visual Studio——带你多工程开发](http://blog.csdn.net/luoweifu/article/details/48915347)

下一篇要讲述的内容： 
带你跳出Runtime Library大坑
***