上一篇文章[带你玩转Visual Studio——带你了解VC++各种类型的工程](http://blog.csdn.net/luoweifu/article/details/48816605#t29)一文中讲了各种类型VC++工程的主要功能和用途。现在将带你一起快速开发c++程序。

有过Java开发经验的人都知道Java的常用开发工具(如Eclipse、Intellij IDEA等)都有非常强大的关键字高亮、智能提示、快速追踪等的功能。那也许你就要问了：进行C++开发的Visual Studio是否也有这个功能呢？首先要说明的是Visual Studio本身并没有这么强大的功能(至少VS2010及之前版本是这样的，有一些简单的代码跟踪能力但是很难用)，但它有一个非常强大和好用的插件有这些功能，它就量VassistX，也称为VC助手，它就是本文要讲的内容。
***

#VassistX的简单介绍与下载安装
##简单介绍
VassistX的全称是Visual Assist X，是whole tomato开发的一个非常好用的插件，可用于VC6.0及Visual Studio的各个版本(包括VS.NET2002、VS.NET2003、VS2005、VS2008、VS2010、VS2012、VS2013及VS2015)。

VassistX有以下主要功能：
**智能提示：**关键字的提示，已有类名、方法名的提示，类成员(成员数据和成员函数)的提示；
**代码高亮：**关键字、类名、方法名等用不同的颜色进行高亮，方便代码的阅读；
**快速追踪：**声明与实现的快速跳转，.cpp与.h文件的快速切换；
**高效查找：**文件名的查找，标识符的查找，标识符补引用的查找；
**代码重构：**重命名标识符(变量名、方法名、类名等，这个非常有用)，自动添加成员变量的Set/Get方法，自动添加函数的注释等。

##下载与安装
###下载：
官方下载地址：[http://www.wholetomato.com/downloads/default.asp](http://www.wholetomato.com/downloads/default.asp)
你也可以到中文的一些网站去下载，网上一搜一大片。

###安装：
安装非常简单，你只需要点击VA_X_Setupxxxx.exe进行默认安装即可，这没什么要说的。

###注册码
还是那句话：自己想办法(以后都不再进行说明)，如果有钱还是支持正版，毕竟作为程序员的我们应该知道写一个好的程序不容易。
***
***

#VassistX的使用指南
##1.通过“Tip of the day”快速学习。
在你安装VassistX后，启动VS时，会有一个帮助提示(如下图)，这是你快速学习VassistX的最好方式，还有小动画提示，一看就懂。如果你看不懂英文，看小动画也能明白怎么回事。
<center>![tip of the day](http://img.blog.csdn.net/20151002001039064)
图 1：tip of the day</center>

如果你不希望每次启动VS时都弹出这个对话框，只需把左下角的"Show tips at startup"的勾选去掉就可以。如果需要再次弹出对话，在菜单中选择VassitX\Visual Assist X Option...-->Starup，把Show tip of the day勾选上即可。
***

##2.主要窗口和工具
插件装上之后你应该就能感觉比以前好多了，比如代码高亮啊，智能提示啊，应该立马就能体现出来。但这还是要简单介绍一下。

<center>![窗口视图](http://img.blog.csdn.net/20151002092339228)
图 2：窗口视图</center>

插件成功安装之后，菜单栏会多一个VassistX的菜单，这里包含了VassistX的所有功能和相关的设置，设置方面后面还会进一步讲。
左侧会有两个VA Outline和VA View视图(如果没有，可能菜单VassistX\Tools\VA Outline调出来)。VA Outline这个视图很有用，也是我用的最多的一个视图，它能清晰地呈现一个类中的各个成员。
工具栏也会多一个VassistX工具组。这个我用的最多的要数最右边的.h与.cpp的切换按钮。
***

##3常用的快捷键
这里只列出一些最常用的快捷键，一般记住这些也就够用了。

|快捷键|说明|备注|
|:---|:---|:--|
|Alt+G|快速跳转，如由声明跳转到实现，由实现跳转到声明。|光标要在标识符处|
|Alt+O|.h与.cpp文件的快速切换||
|Alt+Shift+F|查找标识符所有被引用的位置|光标要在标识符处|
|Alt+Shift+O|查找整个Solution下的某个文件|O指open，打开指定的文件|
|Alt+Shift+S|查找标识符|S指Symbol|
|Alt+Shift+R|重命名标识符|光标要在标识符处,R指ReName|
|Ctrl+Shift+V|选择剪切板的内容进行粘贴||


###更改快捷键
菜单Tools\Option...，然后在打开的对话框中选择Keyboard，Show commands containning中输入VAssistX就能看到VAssistX的各种功能，你可以设置某一指定功能的快捷键。如你输入VAssistX.refactorRename，就能看到重命名的默认快捷键是Shift+Alt+R，你在Press shortcut keys中按下快捷键更改它。
<center>![设置快捷键](http://img.blog.csdn.net/20151002104106480)
图 3：设置快捷键</center>
***
***

#VassistX的高效开发的属性配制

##选项设置
VassistX有些默认设置并不太友好，我们可以自己重新设置它。在菜单中选择VassitX\Visual Assist X Option...打开设置对话框。以下是我个人的偏好设置，仅作参考(只说明一些关键设置的含义)。

<center>![设置1](http://img.blog.csdn.net/20151002124203713)
图 4：设置1</center>
1.拼写错误检测(这个不要选，不然老会有红色的波浪线提示)；
2.类型错误检测(这个选上，可以测试你的变量类型是否正确)；

<center>![设置2](http://img.blog.csdn.net/20151002124215871)
图 5：设置2</center>
1.高亮引用的标识符(设置颜色，一个当前词的颜色，一个是非当前词的颜色)；
2.自动高亮当前光标所在处标识符
3.高亮查找引用的结果；
4.高亮重命名标识符时关联的变量；

<center>![设置3](http://img.blog.csdn.net/20151002124225092)
图 6：设置3</center>
1.(黑色)高亮匹配的括号；
2.(红色)高亮不匹配的括号；
3.高亮当前光标所在的行(可选择高亮前景或高亮背景)；
4.纵向指示器的分隔线，一般用于控制一行代码的字符数；
5.高亮查找结果。
***

##注释配制与自动添加代码
注释也是程序的一个重要组成部分之一，好的注释是提高代码的可读性和程序的可维护性的一个关键因素，而要写大量的注释是一件非常繁琐的事情，给程序员增加了不少负担，而VAsssistX就可能帮我们减轻这种负担。将光标移到函数名处，右键鼠标选择Refactor\Document Method可自动帮我们添加函数的注释。

我们可以自己配制自定义的注释格式。选择菜单：VAssistX\Insert VA Snippet...\Edit VA Snippet...进行设置。给出我的相关设置，仅作参考：

**Title:** File header detailed
**Shortcut:** fh
**Description:** 对整个文件进行注释
```
//===============================================================
//Summary:
//          $FILE_BASE$ 类， $end$
//FileName:
//			$FILE_BASE$.$FILE_EXT$
//Remarks:
//          ...
//Date:
//          $YEAR$/$MONTH$/$DAY$
//Author:
//          %USERNAME%(luoweifu@126.com)
//===============================================================
```
**说明：**两个$符号之间的内容都是VAssistX中定义的宏，参见文后的附录：<a href="#t15">Visual Assist X Snippets 宏</a>
***

**Title:** Refactor Document Method
**Shortcut:** 
**Description:** 对函数进行注释
```
//---------------------------------------------------------------
//function: 
//          $SymbolName$ $end$
//Access:
//          $SymbolVirtual$ $SymbolPrivileges$ $SymbolStatic$
//Parameter:
//          [in] $MethodArg$ - 
//Returns:
//          $SymbolType$ - 
//Remarks:
//          ...
//author:    %USERNAME%[luoweifu]
//---------------------------------------------------------------

```
***

**Title:** #ifndef ... #endif
**Shortcut:** #ifn
**Description:** 防止头文件重复包含
```
#ifndef __$FILE_BASE_UPPER$_H__
#define __$FILE_BASE_UPPER$_H__
$end$
#endif	//__$FILE_BASE_UPPER$_H__

```
***

**Title:** Refactor Encapsulate Field
**Shortcut:** 
**Description:** 添加类中成员变量的Get/Set方法。
```
	$end$$SymbolType$ Get$GeneratedPropertyName$() const
	{
		return $SymbolName$;
	}
	void Set$GeneratedPropertyName$($SymbolType$ val)
	{
		$SymbolName$ = val;
	}

```
***

**Title:**
**Shortcut:** //-
**Description:** 用于某一个重要修改的注释，并记录修改时间。
```
// $end$ [$YEAR$/$MONTH$/$DAY$ %USERNAME%]
```
***

**Title:**
**Shortcut:** ///
**Description:** 分隔线，用于重要的代码块的分隔。
```
//===============================================================
$end$
```
***
***

#附录

##Visual Assist X Snippets 宏

|.|Reserved String|Meaning|样例或说明|
|---|---|---|---|
|Date |$DATE$|Year/month/day formatted as %04d/%02d/%02d | 2015/10/02|
||$DATE_LOCALE$|Current date in locale format|本地化格式境|
||$DAY$|Day of month formatted as %d|2|
||$DAY_02$|Day of month formatted as %02d|02|
||$DAYNAME$|Day abbreviation in locale format|//Fri|
||$DAYLONGNAME$|Full name of day in locale format|//Friday|
||$MONTH$|Month formatted as %d|10|
||$MONTH_02$|Month formatted as %02d|10|
||$MONTHNAME$|Month abbreviation in locale format|Oct|
||$MONTHLONGNAME$|Full name of month in locale format|October|
||$YEAR$|Year formatted as %d|2015|
||$YEAR_02$|Year formatted as %02d|15|
|Time|$HOUR$|Hour formatted as %d|16|
||$HOUR_02$|Hour formatted as %02d|16|
||$MINUTE$|Minute formatted as %02d|29|
||$SECOND$|Second formatted as %02d|30|
|File|$FILE$|Full filename with path*|D:\CppWorkspace\DesignPattern\DesignPattern\Water.h|
||$FILE_UPPER$|Full filename with path in uppercase*|D:\CPPWORKSPACE\DESIGNPATTERN\DESIGNPATTERN\WATER.H|
||$FILE_BASE$|Filename without path or extension*|Water|
||$FILE_BASE_UPPER$|Filename without path or extension in upper case*|WATER|
||$FILE_EXT$|Filename extension*|h|
||$FILE_EXT_UPPER$|Filename extension in upper case*|H|
||$FILE_PATH$|Path of file*|D:\CppWorkspace\DesignPattern\DesignPattern|
||$FILE_PATH_UPPER$|Path of file in upper case*|D:\CPPWORKSPACE\DESIGNPATTERN\DESIGNPATTERN|
|General|$clipboard$|Current clipboard|当前剪贴板内容|
||$end$|Position of caret after expansion|输入完成光标位置|
||$selected$|Current selection**|选定内容|
||$$|Literal '$' character|$转义|
|Symbol Context|$MethodName$|Name of containing method|||
||$MethodArgs$|Method parameters|函数参数列表|
||$ClassName$|Name of containing class|类名称|
||$BaseClassName$|Name of base class of containing class|基类名称|
||$NamespaceName$|Fully qualified namespace name|命名空间|
|GUID|$GUID_DEFINITION$|Generated GUID formatted for use in a definition|GUID定义，“,”分割|
||$GUID_STRING$|Generated GUID formatted for use in a string|GUID字符串，“-”分割|
||$GUID_STRUCT$|Generated GUID formatted for use in a struct|GUID结构|
||$GUID_SYMBOL$|Generated GUID formatted with underscores|GUID符号，"_"分割|
||$GUID_STRING_UPPER$|Uppercase version of $GUID_STRING$|略|
||$GUID_STRUCT_UPPER$|Uppercase version of $GUID_STRUCT$|略|
||$GUID_SYMBOL_UPPER$|Uppercase version of $GUID_SYMBOL$|略|
||The following reserved strings are available only in refactoring snippets|
|Refactor|$GeneratedPropertyName$|Property name generated during Encapsulate Field|与类属性同名的访问方法，首字符大写（类似Java中的Set/Get方法）|
||$generatedPropertyName$|Same as $GeneratedPropertyName$ but with lower-case first letter|与类属性同名的访问方法，首字符小写|
||$MethodArg$|One parameter of the method and its type|不可用|
||$MethodArgName$|One parameter of the method|方法参数|
||$MethodArgType$|Type of one parameter of the method|函数体|
||$MethodBody$|Body of implementation|函数体|
||$MethodQualifier$|Optional qualifiers of method|尚不清楚|
||$ParameterList$|Parameters separated by commas|参数列表|
||$SymbolContext$|Context and name of method|函数全名（含类信息等）|
||$SymbolName$|Name of method|函数名称|
||$SymbolPrivileges$|Access of method|访问控制|
||$SymbolStatic$|Keyword static or blank|static|
||$SymbolType$|Return type of method|函数返回类型|
||$SymbolVirtual$|Keyword virtual or blank|virtual|
