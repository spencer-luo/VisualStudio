[编程思想之多线程与多进程(4)——C++中的多线程](http://blog.csdn.net/luoweifu/article/details/46835437)一文中讲了VC++的多线程的用法和用例，本文接着这个话题作进一步的讲解。如果你是初次接触C++多线程或想对多线程与多进程的基础有进一步了解，可查看以下文章：《[编程思想之多线程与多进程(1)——以操作系统的角度述说线程与进程](http://blog.csdn.net/luoweifu/article/details/46595285)》、《[编程思想之多线程与多进程(2)——线程优先级与线程安全](http://blog.csdn.net/luoweifu/article/details/46701167)》、《[编程思想之多线程与多进程(4)——C++中的多线程](http://blog.csdn.net/luoweifu/article/details/46835437)》
***

#SuspendThread和ResumeThread
从[编程思想之多线程与多进程(1)——以操作系统的角度述说线程与进程](http://blog.csdn.net/luoweifu/article/details/46595285)一文中我们知道：操作系统的线程有几种状态的变化：执行(运行)，挂起（阻塞）和恢复(就绪)执行。
当线程做完任务或者现在想暂停线程运行，就需要使用SuspendThread来暂停线程的执行，当然恢复线程的执行就是使用ResumeThread函数了。这两个函数使用很简单的，下面就来看看例子是怎么样使用的。

函数原型如下：
挂起线程
	DWORD WINAPI SuspendThread(_In_ HANDLE hThread);

恢复线程
	DWORD WINAPI ResumeThread(_In_ HANDLE hThread);

说明：hThread为指定线程的句柄。

继续[编程思想之多线程与多进程(4)——C++中的多线程](http://blog.csdn.net/luoweifu/article/details/46835437)一文中的同步线程代码：

```C++
#define NAME_LINE   40

//定义线程函数传入参数的结构体
typedef struct __THREAD_DATA
{
	int nMaxNum;
	char strThreadName[NAME_LINE];

	__THREAD_DATA() : nMaxNum(0)
	{
		memset(strThreadName, 0, NAME_LINE * sizeof(char));
	}
}THREAD_DATA;

HANDLE g_hMutex = NULL;     //互斥量

							//线程函数
DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	THREAD_DATA* pThreadData = (THREAD_DATA*)lpParameter;

	for (int i = 0; i < pThreadData->nMaxNum; ++i)
	{
		//请求获得一个互斥量锁
		WaitForSingleObject(g_hMutex, INFINITE);
		std::cout << pThreadData->strThreadName << " --- " << i << std::endl;
		Sleep(100);
		//释放互斥量锁
		ReleaseMutex(g_hMutex);
	}
	return 0L;
}
```

我们改一下测试代码，如下：

```C++
void Test()
{
	//创建一个互斥量
	g_hMutex = CreateMutex(NULL, FALSE, NULL);

	//初始化线程数据
	THREAD_DATA threadData1, threadData2;
	threadData1.nMaxNum = 5;
	strcpy_s(threadData1.strThreadName, "线程1");
	threadData2.nMaxNum = 10;
	strcpy_s(threadData2.strThreadName, "线程2");


	//创建第一个子线程
	HANDLE hThread1 = CreateThread(NULL, 0, ThreadProc, &threadData1, 0, NULL);
	//创建第二个子线程
	HANDLE hThread2 = CreateThread(NULL, 0, ThreadProc, &threadData2, 0, NULL);

	// 挂起线程
	SuspendThread(hThread1);					// [代码段1]

	//Sleep(500);									// [代码段2]
	//ResumeThread(hThread1);						// [代码段2]

	//关闭线程
	CloseHandle(hThread1);
	CloseHandle(hThread2);

	system("pause");
}
```

当我们打开[代码段1]，注释[代码段2]时，结果如下：
>线程2 --- 0
线程2 --- 1
线程2 --- 2
线程2 --- 3
线程2 --- 4
线程2 --- 5
线程2 --- 6
线程2 --- 7
线程2 --- 8
线程2 --- 9

可以发现线程1被挂起，并没有执行。

当我们同时打开[代码段1]和[代码段2]，结果如下：
>线程2 --- 0
线程2 --- 1
线程2 --- 2
线程2 --- 3
线程2 --- 4
线程1 --- 0
线程2 --- 5
线程1 --- 1
线程2 --- 6
线程1 --- 2
线程2 --- 7
线程1 --- 3
线程2 --- 8
线程1 --- 4
线程2 --- 9

可以发现线程1在0.5秒之后才开始执行，这是因为线程1在挂起0.5秒之后才被唤醒(恢复)，开始执行。


#线程与同步锁的封装类
##封装类源代码
```C+++
#ifndef CTHREAD_H_

#include <windows.h>

// 封装的线程类
class CThread 
{
public:
	CThread()
		: m_bStopped(false)
	{
		m_hThread = CreateThread(NULL, 0, StartRoutine, this, CREATE_SUSPENDED, &m_nId);
	}

	virtual ~CThread()
	{
		if (m_hThread) {
			CloseHandle(m_hThread);
		}
	}

protected:
	// 执行函数，子类应该实现这个方法，否则线程什么也不做
	virtual void Run()
	{
	}

public:
	// 开始执行线程
	virtual void Start()
	{
		ResumeThread(m_hThread);
	}

	// 线程是否停止
	bool Stopped()
	{
		return m_bStopped;
	}


	void Join()
	{
		if (m_hThread) {
			WaitForSingleObject(m_hThread, INFINITE);
		}
	}

private:
	// 线程执行的起始地址，也叫线程函数
	static DWORD WINAPI StartRoutine(LPVOID param)
	{
		CThread * thread = (CThread*)param;
		thread->Run();
		thread->m_bStopped = true;
		return 0;
	}

private:
	HANDLE			m_hThread;		// 线程句柄
	bool			m_bStopped;		// 线程是否停止
	DWORD			m_nId;			// 线程ID
};

// 封装的互斥量类
class CMutex 
{

public:
	CMutex()
	{
		// 创建互斥量锁
		m_hMutex = CreateMutex(NULL, FALSE, NULL);
	}
	~CMutex()
	{
		// 释放互斥量锁
		if (m_hMutex)
			CloseHandle(m_hMutex);
	}

public:
	// 加锁，获取互斥量锁，锁定资源
	bool Lock()
	{
		if (m_hMutex) 
		{
			return WaitForSingleObject(m_hMutex, INFINITE) == WAIT_OBJECT_0;
		}
		return false;
	}

	// 试图锁定资源，判断当前的互斥量是否被占用。
	// 返回true说明该锁为非占用状态，可获得该锁；返回false说明该锁为占用状态，需等待被释放
	bool TryLock()
	{
		if (m_hMutex) {
			return WaitForSingleObject(m_hMutex, 0) == WAIT_OBJECT_0;
		}
		return false;
	}

	// 解锁，释放互斥量锁
	void Unlock()
	{
		if (m_hMutex)
			ReleaseMutex(m_hMutex);
	}

private:
	HANDLE			m_hMutex;		// 互斥量句柄
};

// 互斥量锁的抽象
// 只要声明该对象即锁定资源，当退出其(该对象)作用域时即释放锁
class CLock 
{
public:
	CLock(CMutex &mutex)
		: m_mutex(mutex)
	{
		m_bLocked = m_mutex.Lock();
	}

	~CLock()
	{
		if (m_bLocked)
			m_mutex.Unlock();
	}

private:
	// 禁用赋值操作符
	CLock & operator = (CLock&)
	{
		return *this;
	}

private:
	CMutex&			m_mutex;		// 互斥量句柄的引用
	bool			m_bLocked;		// 互斥量是否被锁定(占用)
};

#endif	// CTHREAD_H_
```

##测试程序
```C+++
#include <iostream>
#include <string>
#include "CThread.h"

CMutex g_metux;

class TestThread : public CThread
{
public:
	TestThread(const std::string& strName)
		: m_strThreadName(strName)
	{
	}

	~TestThread()
	{
	}

public:
	virtual void Run()
	{
		for (int i = 0; i < 50; i ++)
		{
			CLock lock(g_metux);
			std::cout << m_strThreadName << ":" << i << std::endl;
			//Sleep(100);
		}
	}
private:
	std::string m_strThreadName;
};


int main()
{
	TestThread thread1("Thread1");
	thread1.Start();
	TestThread thread2("Thread2");
	thread2.Start();
	
	system("pause");
    return 0;
}

```

##结果
>Thread1:1
Thread2:1
Thread1:2
Thread2:2
Thread1:3
Thread2:3
Thread1:4
Thread2:4
Thread1:5
Thread2:5
Thread1:6
Thread2:6
Thread1:7
Thread2:7
Thread1:8
Thread2:8
Thread1:9
Thread2:9
Thread1:10
Thread2:10
Thread1:11
Thread2:11
......

#多线程调试
选择"Debug->Windows->Threads"菜单调出线程监视窗口。在这里你能看到程序中的所有线程，打断点单步调试，你会看到执行路径在线程与线程之间切换。


***
***

上一篇回顾： 
[ 带你玩转Visual Studio——VS2015的新功能和特性](http://blog.csdn.net/luoweifu/article/details/51418247)

下一篇要讲述的内容： 
带你玩转Visual Studio——性能分析
***
