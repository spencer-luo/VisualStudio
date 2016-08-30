上一篇文章[带你玩转Visual Studio——带你管理多种释出版本](http://blog.csdn.net/luoweifu/article/details/48912241)让我们了解了Debug与Release的区别，并学会也如果管理 多个不同释出版本的配制项。在一个大型的项目中，往往不止一个工程，而会有多个工程相互关联，每个工程也都会有自己的释出版本，这就是这篇文章将要讲述的内容。
***
#一个Solution多个Project
##多个工程简介
在[带你玩转Visual Studio——带你新建一个工程](http://blog.csdn.net/luoweifu/article/details/48692267)一文中提到一个Solution(解决方案)可以有多个Project(工程)，那什么时候需要有多工程呢？ 多工程又有什么好处呢？

**应用场景：**当一个项目由多个不同的组件(模块)构成时，为每一个组件创建一个工程，所有的组件工程在同一个解决方案下。
**优点：**结构清晰，可进行分模块开发，对复杂程序进行解耦。

##创建一个多工程项目
我们还是以Utils这个工程为例，在[带你发布自己的工程库](http://blog.csdn.net/luoweifu/article/details/48895765)一文及上一篇[带你管理多种释出版本](http://blog.csdn.net/luoweifu/article/details/48912241)中已经创建了一个Utils工程，并为它编译出了多个版本的库，但我们使用这个库的时候却是在另一个Solution下进行的，其实我们完全可以而且也应该把使用Utils库的工程与Utils工程放在一个解决方案下。

1. **新建Project添加到已有Solution中**，File->New->Project... 打开新建工程对话框新建一个UsingUtils工程，注意在Solution这一栏中我们选择Add to solution。
<center>![添加一个工程](http://img.blog.csdn.net/20151005180802552)
添加一个工程</center>

2. **添加引用关联**，这时我们要使用这个Utils编译出来的库，配制也要简单一点了。右键UsingUtils工程->Properties->Common Properties->Framework and references，添加引用(依赖)的工程Utils。设置引用关联后，如果Utils工程发生改动或更新，在编译UsingUtils工程时就会重新编译Utils工程。
<center>![添加引用关联](http://img.blog.csdn.net/20151005220228885)
添加引用关联</center>

3. **设置头文件的路径**。
<center>![设置头文件的路径](http://img.blog.csdn.net/20151005220611477)
设置头文件的路径</center>

4. **设置启动工程**，在有多个工程的Solution中要设置启动工程(也就是要第一个开始执行的工程)，不然你按F5运行时不知道从哪个工程开始执行。选择UsingUtils工程名右键鼠标->Set as Startup Project。然后就可以执行或调试UsingUtils工程了。
***

#编译结果和目录管理
在多个组件同时开发时，把相关的Project放在同一个Solution下会方便很多。但你有没有发现一个新的问题，如果一个Solution有很多的Project，每一个Project目录下都会有一个编译结果的目录，如下图这样你昏不昏？
![编译结果目录](http://img.blog.csdn.net/20151005223002754)
编译结果目录

那如何管理这些目录，使这些目录看起来不这么混乱呢？其实我们是可以设置这些目录的输出路径的，可以把它们放在一起管理。我们可以将输出目录设计成这样：

- Utils
	- Utils
	- UsingUtils
	- Output
		- Win32
			- Debug
				- Bin
				- Lib
				- Temp
			- Release
				- Bin
				- Lib
				- Temp
		- Linux
			- Debug
				- Bin
				- Lib
				- Temp
			- Release
				- Bin
				- Lib
				- Temp

这样看起来是不是结构清晰多了！Output为输出目录，Win32为Windows X32下编译的结构，Linux为Linux平台下的编译结果(这个涉及到跨平台开发，暂时不谈)，Win32下再有Debug和Release等多个不同的释出版本，Bin下放置编译出的最终结果(如.exe等)，Lib下放置编译出的所有.lib文件，Temp放置编译过程的临时文件(如.obj等)。

我们还是以Utils为例进行说明。Utils Solution下有两个Project：Utils(编译出Utils工具库)和UsingUtils(使用Utils的库)，仅以释出Debug_Static进行说明，其它的释出方式与此类似。

1. **所有Project使用同一组配制项。**
什么意思呢？我们在[带你玩转Visual Studio——带你管理多种释出版本](http://blog.csdn.net/luoweifu/article/details/48912241)一文说到Debug和Release就是一组配制项，其实整个Solution有一个配制项，每一个Project也有自己的配制项。
整个Solution的配制项也就是下图工具栏中你能看到的这些配制项：
<center>![Solution的配制项](http://img.blog.csdn.net/20151007114313056)
Solution的配制项</center>
而每一个Project的配制荐是你右键工程名->Properties能看到的配制项：
<center>![Project的配制项](http://img.blog.csdn.net/20151007114200856)
Project的配制项</center>
一般一个Solution下的所有的Project最好使用同组配制项，这样不容易混乱。

2. **给UsingUtils添加Debug_Static配制项。**我们设置Utils的属性时已经配制了Debug_Static的配制项，并设置了Solution的Debug_Static配制项，再给UsingUtils添加Debug_Static的配制项。
<center>![添加配制项](http://img.blog.csdn.net/20151007121337915)
添加配制项</center>
标“4”的Create new solution configurations表示为整个Solution也添加(Debug_Static)配制项，这个复选框得取消勾选，因为设置Utils时已经为Solution默认添加了Debug_Static配制项，不然会添加不上。

3. **设置Utils的输出路径**，右键Utils工程->Properties进行如下配制。
<center>![设置输出路径](http://img.blog.csdn.net/20151007122645601)
设置输出路径</center>

4. **拷贝导出库.lib**，我们可以将Utils编译出的静态库拷贝Utils.lib到Lib目录下，这样我们就可以直接把这个文件提供到调用方使用。
<center>![这里写图片描述](http://img.blog.csdn.net/20151007122947475)
</center>
Build Events中可以设置编译前、链接前、编译后要进行的处理事件。这里我们目地是编译后将编译出的Utils.lib拷贝到Lib文件夹下，所以我们在Post-Build Event输入以下命令
```
:如果Lib目录不存在，侧创建这个目录
if not exist $(SolutionDir)Output\Win32\$(Configuration)\Lib md $(SolutionDir)Output\Win32\$(Configuration)\Lib
:将(ProjectName).lib文件拷贝到Lib目录下
copy /y $(SolutionDir)Output\Win32\$(Configuration)\Bin\$(ProjectName).lib $(SolutionDir)Output\Win32\$(Configuration)\Lib\
```

5. **设置UsingUtils的输出路径**，与Utils类似如下：
<center>![设置UsingUtils的输出路径]
(http://img.blog.csdn.net/20151007123802554)
设置UsingUtils的输出路径</center>

6. **设置完成**，Ok，编译一下再来看看输出结果目录，是不是清晰多了！
![新的输出结果目录](http://img.blog.csdn.net/20151007124115753)
新的输出结果目录
***
***

上一篇回顾： 
[带你玩转Visual Studio——带你管理多种释出版本](http://blog.csdn.net/luoweifu/article/details/48912241)

下一篇要讲述的内容： 
带你玩转Visual Studio——带你多工程开发
***
