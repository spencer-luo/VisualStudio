上一篇文章[带你玩转Visual Studio——单元测试](http://blog.csdn.net/luoweifu/article/details/51534627)讲了VisualStudio中单元测试的用法。在VC++开发和调试中，有时无法设置断点进去调试(如我曾经遇到过的浏览器插件的开发，因为是浏览器调用开发的插件DLL，所以无法在VS中按F5运行的方式进行断点调试)，这时就需要用过绑定进程的方式，进行调试。

***
###在要设置判断的地方创建提示框
为方便起见，我们直接在main方法中创建对话框来进行调试。
![这里写图片描述](http://img.blog.csdn.net/20160602222009169)

###执行程序
 编译成功后，点击程序的可执行文件(.exe文件)开始运行。这里会出现提示对话框Debug Dialog：
<center> ![Debug Dialog](http://img.blog.csdn.net/20160602222333814)
 Debug Dialog</center>
 ###绑定进程
 选择菜单Debug->Attach to Process... 打开绑定进程对话框
<center> ![绑定进程](http://img.blog.csdn.net/20160602230314951)
绑定进程</center>

选择要绑定的进程，点击"Attach"就可以进行调试了。
***
***

上一篇回顾： 
[带你玩转Visual Studio——单元测试](http://blog.csdn.net/luoweifu/article/details/51534627)

下一篇要讲述的内容： 
带你玩转Visual Studio——带你多工程开发
***
