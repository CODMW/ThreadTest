
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <thread>
//#include 
//修改1-v3.0-on git
#define MAX_THREADS 10
#define MAX_BUF_SIZE 255

//多线程

//定义一个结构体
typedef struct _MyData
{
	int id;
	int val2;
}MyData, *pMyData;


void  Myprintf(int i)
{
	Sleep(100);
	printf("线程 %d --》准备工作 \n", i);
	Sleep(150);
	printf("线程 %d --》工作中...\n", i);
	Sleep(200);
	printf("线程 %d --》工作完结束\n", i);
}


//线程执行函数
DWORD WINAPI MyThreadPro(LPVOID lpParam)
{
	MyData* pa = (MyData*)lpParam;
	printf("启动线程:%d \n", pa->id);
	Myprintf(pa->id);
	return 0;


	//返回调用进程的默认内存堆句柄。
}



void main()
{
	//创建线程1        //注：在MFC程序中，应该调用AfxBeginThread函数，在Visual C++程序中应调用_beginthreadex函数，  _endthread来销毁线程。
	/*HANDLE CreateThread(
	LPSECURITY_ATTRIBUTES lpThreadAttributes, // SD
	SIZE_T dwStackSize,                       // initial stack size
	LPTHREAD_START_ROUTINE lpStartAddress,    // thread function
	LPVOID lpParameter,                       // thread argument
	DWORD dwCreationFlags,                    // creation option
	LPDWORD lpThreadId                        // thread identifier
	);
	*/
	pMyData pData;
	DWORD dwThreadId[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];
	        
	//for循环创建多个线程
	for (int i = 0; i < MAX_THREADS; i++)
	{
		//参数数据
		pData = (pMyData)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof MyData);  //即在进程默认堆内存上申请了一个不可移动的空间，大小为sizeof(Data)的内存空间
		if (pData == NULL)
			ExitProcess(2);
		pData->id = i;
		pData->val2 = i + 100;

		//创建线程
		hThread[i] = CreateThread(NULL, 0, MyThreadPro, pData, 0, &dwThreadId[i]);
		if (hThread[i] == NULL)
		{
			ExitProcess(i);
		}

		Sleep(120);
	}

	//等待所有线程结束
	WaitForMultipleObjects(MAX_THREADS, hThread, true, INFINITE);

	//通过CloseHandle函数来关闭该线程对象
	for (int i = 0; i < MAX_THREADS; i++)
	{
		CloseHandle(hThread[i]);
	}

	printf("hello....\n");  //线程结束后执行
	system("pause");
	return;
}
