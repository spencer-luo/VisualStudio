上一篇文章[带你玩转Visual Studio——带你新建一个工程](http://blog.csdn.net/luoweifu/article/details/48692267)一文中提到新建一个工程时会有很多的工程类型(图1)，现在将简单介绍各种类型工程的含义和主要用途。由于这里包含的工程类型太多，有很多本人也没有接触过，有些可能理解的不太对的地方还请谅解。

<center>![New Project](http://img.blog.csdn.net/20150924225250115)
图 1：New Project</center>
***

#理解几个概念
在开讲之前先大概理解几个概念，这是理解后面各种工程含义的基础。
##COM
**COM(Component Object Model)组件对象模型**是microsoft制定的一个组件软件标准，跟unix上的CORBA一样。凡是遵循COM标准开发出来的组件称为COM组件。目地是实现二进制方式的软件重用 。在windows平台上，COM的实现形式有DLL(进程内组件)和EXE(进程外组件)2种。

##OLE
**OLE(Object Linking and Embedding)对象连接与嵌入**是一种面向对象的技术，利用这种技术可开发可重复使用的软件组件COM。OLE是软件比较早提出的一种技术，现在OLE中的很多技术已经融合到其它的技术中了，如COM、ActiveX。

##ATL
**ATL(Active Template Library)活动模板库**是一套C++模板库，常用于开发COM程序和ActiveX程序。要理解ATL技术可从以下两方面理解：
1.ATL可以说是把COM封装了一下，象MFC一样做成一个库，并有一个向导，使COM应用开发尽可能地自动化、可视化，这就决定了ATL只面向COM开发提供支持。
2.ATL因其采用了特定的基本实现技术，摆脱了大量冗余代码，使用ATL开发出来的COM应用的代码简练高效。
在ATL产生以前，开发COM组件的方法主要有两种：一是使用COM SDK(COM软件开发包)直接开发COM组件，另一种方式是通过MFC提供的COM支持来实现。而现在 ATL已经成为Microsoft支持COM应用开发的主要开发工具。

##MFC
**MFC(Microsoft Foundation Classes)微软基础类**是微软提供的一个用于Windows程序开发的基础类库。MFC以C++类的形式封装了Windows的API，并且包含一个应用程序框架，以减少应用程序开发人员的工作量。其中包含的类包含大量Windows句柄封装类和很多Windows的内建控件和组件的封装类。

##ActiveX
ActiveX是微软提出的一组使用COM技术使得软件组件在网络环境中进行交互的技术集，它与具体的编程语言无关。作为针对Internet应用开发的技术，ActiveX被广泛应用于WEB服务器以及客户端的各个方面。同时，ActiveX技术也被用于方便地创建普通的桌面应用程序，此外ActiveX一般具有界面。

ActiveX既包含服务器端技术，也包含客户端技术。其主要内容是：   
1. ActiveX控制（ActiveX   Control）；用于向WEB页面、Microsoft   Word等支持ActiveX的容器（Container）中插入COM对象。
2. ActiveX文档（ActiveX   Document）；用于在WEB   Browser或者其它支持ActiveX的容器中浏览复合文档（非HTML文档），例如Microsoft   Word文档，Microsoft   Excel文档或者用户自定义的文档等。
3. ActiveX脚本描述（ActiveX   Scripting）；用于从客户端或者服务器端操纵ActiveX控制和Java程序，传递数据，协调它们之间的操作。
4. ActiveX服务器框架（ActiveX   Server   Framework）；提供了一系列针对WEB服务器应用程序设计各个方面的函数及其封装类，诸如服务器过滤器、HTML数据流控制等。   
5. 在Internet   Explorer中内置Java虚拟机(Java   Virtual   Machine)，从而使Java   Applet能够在Internet   Explorer上运行，并可以与ActiveX控制通过脚本描述语言进行通信。



#各种工程结构
##ATL
ATL(Active Template Library)活动模板库，是一种微软程序库，支持利用C++语言编写ASP代码以及其它ActiveX程序。通过
###ATL Project

##CLR
###Class Library
###CLR Console Application
###CLR Empty Project
###Windows Forms Application
###Windows Forms Control Library

##General
###Empty
###Custom Wizard
###Makefile Project

##MFC
###MFC ActiveX Control
###MFC Application
###MFC DLL

##Test
###Test

##Win32
###Win32 Console Application
###Win32 Project

#说明 
其中常用的工程类型也就几种：
Win32 Console Application
Win32 Project
MFC Application




(本文未完，明日继续……)