上一篇文章[带你玩转Visual Studio——带你高效开发](http://blog.csdn.net/luoweifu/article/details/48852119)通过对VAssistX优秀插件的讲解，让我们掌握了快速开发C++代码的技能。然而大部分的程序都不是一个人的开发的，是由一个团队的多个人一起开发的，大型的系统还可能由多个不同的团队分包进行开发。多人进行协作开发时，代码的管理就显得及为重要，需要借助代码管理工具的辅助，这种工具又称为**版本控制系统**。

目前主流的版本控制系统有：
**CVS：**是一个用于代码版本控制的自由软件，它是一个比较早出现的工具，由于它有很多自身的缺陷，现在几乎被SVN所取代了。
**SVN：**SVN是Subversion的简称，它是集中式的版本控制系统。SVN继承了CVS的基本思想，包含了CVS的几乎所有功能。你可以认为SVN是CVS的升级版(但实际上它们完全是两个软件)。
**GIT：**GIT是分布式的版本控制系统。相信玩过开源代码的都知道[github](https://github.com/)吧，它就是一个基于git的代码托管平台。
关于SVN与GIT的区别，可参考：[GIT和SVN之间的五个基本区别](http://www.vaikan.com/5-fundamental-differences-between-git-svn/)

**本文假设您已经对SVN有基本的了解和掌握，并用TortoiseSVN客户端进行过代码的迁入、选出、更新等功能进行团队的协作开发。如果没有这方面的知识，建议先查阅其它的相关资料，以对SVN有大致的了解后再来阅读本文。**

#VisualSVN的简单介绍与下载安装
##简介
VS2010有一个自带的版本管理工具，也就是菜单中的Team(团队协作)，但用过的人应该都知道非常难用，与SVN和GIT相比已经被甩出几条街了。
所以很多的公司或团队会选择SVN来进行代码的管理，安装一个SVN的客户端进行的迁入与迁出。但可能很少人知道VS上还有一个插件可以帮助我们更好地使用SVN，它就是**VisualSVN**。

VisualSVN是一个用在Visual Studio上的插件，SVN的客户端TortoiseSVN(SVN有一个服务器Server用于集中管理资源库，有一个客户端Client用于团队的每一个成员进行访问资源库、提交代码和迁出代码等。)是一个版本控制工具。VisualSVN是基于TortoiseSVN的，也就是说VisualSVN要调用TortoiseSVN软件的功能，所以要使用VisualSVN，必须同时安装VisualSVN和TortoiseSVN。


##下载
VisualSVN的官方下载地址：
[https://www.visualsvn.com/visualsvn/download/](https://www.visualsvn.com/visualsvn/download/)
SVN的官方下载地址：
[http://tortoisesvn.net/downloads.html](http://tortoisesvn.net/downloads.html)
**注意：**SVN的版本要和VisualSVN的版本对应，也就是要下载给定的VisualSVN版本建议的SVN的版本。如VisualSVN5.1.2可用的SVN版本是1.8.x、1.9.x，建议的SVN版本是 TortoiseSVN 1.9.2.

##安装
安装这个很简单，一般先安装TortoiseSVN再安装VisualSVN。选择默认的设置就可以，这个不多说了。

#VisualSVN的常用功能介绍

##向服务器上传一个工程
关于SVN环境的搭建是另外一个主题，你可以自己去查找相关的资料，这里只讲VS相关的东西。您也可以参考这篇文章：[Windows下的SVN环境搭建详解](http://www.cnblogs.com/oyjt/p/3295801.html)，个人觉得写的还可以。要是在公司里一般会有已经搭建好的SVN环境，你只需要一个代码存放的地址。

现在假设你已经搭建好了SVN的环境，有一个SVN的工作地址：svn://localhost/CppRepos(这是我本SVN机服务器的库地址，远程服务器的地址也是一样的)，有一个SVN的用户名(luoweifu)和密码(svn_luoweifu)。现在要把本机D:\CppWorkspace\DesignPattern下的DesignPattern工程上传到服务器，以后在VS2010下开发这个工程并在VS2010提交和更新代码。基本的操作流程如下：

1. 用VS2010打开DesignPattern工程。安装完VisualSVN插件后，VS上会多一个菜单项VisualSVN。
2. 选择菜单VisualSVN\Add Solution to Subversion...

3. 选择要添加工程的本地路径，一般会自动给你设置好，如果路径是正确的就直接一步。
<center>![Add Solution to Subversion 1](http://img.blog.csdn.net/20151003181539055)
图 1：Add Solution to Subversion 1</center>

4. 这里我们选择Existing Repository，因为我们已经有一个SVN的地址，如果服务器没有创建对应的库可选择New Repository创建一个新的库。
<center>![Add Solution to Subversion 2](http://img.blog.csdn.net/20151003181607964)
图 2：Add Solution to Subversion 2</center>

5. 这里填入你的SVN的地址：svn://localhost/CppRepos
<center>![Add Solution to Subversion 3](http://img.blog.csdn.net/20151003181624374)
图 3：Add Solution to Subversion 3</center>

7. 点击Import就可以了，这时你的VS会有一个Pending Changes的视图，如果没有可通过View\Other Windows\Pending Changes菜单调出来。这个视图将显示所有你要添加到服务器的文件。
<center>![Add Solution to Subversion 4](http://img.blog.csdn.net/20151003181646036)
图 4：Add Solution to Subversion 4</center>

8. Import后只是将本地的文件与服务器上的地址做了映射，并没有真正将文件上传到服务器。你需要将所有文件提交(Commit)，才是真正上传到服务器。选中Pending Changes中的所有文件并右键Commit。
<center>![Add Solution to Subversion 5](http://img.blog.csdn.net/20151003181719811)
图 5：Add Solution to Subversion 5</center>

9. 对话框的底部会显示你要提交的所有文件，你可以勾选要提交或不提交哪些文件。写上你提交的原因或备注(这个很重要，一定要有这样的习惯，以便后期查看历史记录时一看就能知道你做了什么)，然后点击Ok就可以了。
<center>![Add Solution to Subversion 6](http://img.blog.csdn.net/20151003181737668)
图 6：Add Solution to Subversion 6</center>

10. 第一次提交会要求输入用户名和密码，输入你的SVN用户名和密码就可以了。
<center>![Add Solution to Subversion 7](http://img.blog.csdn.net/20151003181749466)
图 7：Add Solution to Subversion 7</center>

##VisualSVN的主要功能
VisualSVN有TortoiseSVN的几乎所有功能，它的作用就是将TortoiseSVN集成到VS中，这样代码的编码、代码的管理就可以都在一个IDE中进行，而不用每次提交或更新代码都要切换到TortoiseSVN去做。这跟Java的MyEclipse、Intellij IDEA的SVN插件是类似的。

添加VisualSVN插件后，VisualSVN菜单会有TortoiseSVN的几乎所有功能。如将Solution添加到服务器，从服务器获得Solution，更新代码、提交代码，打分支、合并分支等，如下图。这些功能只要你对SVN有大致的了解，模索模索就会用了，不再过多的介绍。

<center>![VisualSVN的整体视图](http://img.blog.csdn.net/20151003185827579)
图 8：VisualSVN的整体视图</center>
Pending Chages视图将显示所有新添加、删除或被改动的文件。
Solution Explorer视图对不同状态的文件也会用不同颜色的圆点标注：绿色表示未做更改的文件，黄色表示已做改动或新添加的文件。

##C++工程上传服务器要忽视的文件
在[带你玩转Visual Studio——带你新建一个工程](http://blog.csdn.net/luoweifu/article/details/48692267)一文中讲到了C++工程中的各种类型文件，然后我们在代码的版本控制时有很多文件和目录并不需要上传到服务器。因为服务器中只需要存一些有用的数据和文件，一些无用的辅助性文件(如pch文件，Debug目录等)只会给服务器和管理带来负担。这里将列出需要上传和不需要上传的文件类型。

###需要上传的文件类型：
>h: 头文件
>cpp: 源文件
>txt: 说明文件，如readme
>rc: 资源文件
>rc2: 资源文件
>ico: 图标，如logo等
>sln: 解决方案工程文件
>vcxproj: 工程文件
>filters: 文件过虑器

###不要上传的文件类型
>Debug、Release等编译结构目录
>ipch目录
>aps: last resource editor state
>exe: build result
>idb: build state
>ipch: build helper
>lastbuildstate: build helper
>lib: build result. Can be 3rd party
>log: build log
>manifest: build helper. Can be written yourself.
>obj: build helper
>pch: build helper
>pdb: build result
>res: build helper
>sdf: intellisense dbase
>suo: solution user options
>tlog: build log
>user: debug settings. Do preserve if just one dev or custom debug settings

如果用TortoiseSVN进行管理，需要手动添加ignore属性将不需要上传的文件忽略掉。在你工程目录里，右键->TortoiseSVN->Properties->New->Other，弹出的对话框中Property name中选择svn:ignore，Property value中填入要忽略的内容(这里可以使用能配符)，如下图。
<center>![添加ingore属性](http://img.blog.csdn.net/20151003193552632)
图 9：添加ingore属性</center>
用VisualSVN进行上传Solution时，默认就帮你设置好了，将不需要的文件给屏蔽了。这也是VisualSVN的一大好处。
***
***

上一篇回顾： 
[带你玩转Visual Studio——带你高效开发](http://blog.csdn.net/luoweifu/article/details/48852119)

下一篇要讲述的内容： 
带你玩转Visual Studio——带你管理多种释出版本
***