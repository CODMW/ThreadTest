
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <thread>
//#include 
//�޸�1-v2.0
#define MAX_THREADS 10
#define MAX_BUF_SIZE 255

//���߳�

//����һ���ṹ��
typedef struct _MyData
{
	int id;
	int val2;
}MyData, *pMyData;


void  Myprintf(int i)
{
	Sleep(100);
	printf("�߳� %d --��׼������ \n", i);
	Sleep(150);
	printf("�߳� %d --��������...\n", i);
	Sleep(200);
	printf("�߳� %d --�����������\n", i);
}


//�߳�ִ�к���
DWORD WINAPI MyThreadPro(LPVOID lpParam)
{
	MyData* pa = (MyData*)lpParam;
	printf("�����߳�:%d \n", pa->id);
	Myprintf(pa->id);
	return 0;


	//���ص��ý��̵�Ĭ���ڴ�Ѿ����
}



void main()
{
	//�����߳�1        //ע����MFC�����У�Ӧ�õ���AfxBeginThread��������Visual C++������Ӧ����_beginthreadex������  _endthread�������̡߳�
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
	        
	//forѭ����������߳�
	for (int i = 0; i < MAX_THREADS; i++)
	{
		//��������
		pData = (pMyData)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof MyData);  //���ڽ���Ĭ�϶��ڴ���������һ�������ƶ��Ŀռ䣬��СΪsizeof(Data)���ڴ�ռ�
		if (pData == NULL)
			ExitProcess(2);
		pData->id = i;
		pData->val2 = i + 100;

		//�����߳�
		hThread[i] = CreateThread(NULL, 0, MyThreadPro, pData, 0, &dwThreadId[i]);
		if (hThread[i] == NULL)
		{
			ExitProcess(i);
		}

		Sleep(120);
	}

	//�ȴ������߳̽���
	WaitForMultipleObjects(MAX_THREADS, hThread, true, INFINITE);

	//ͨ��CloseHandle�������رո��̶߳���
	for (int i = 0; i < MAX_THREADS; i++)
	{
		CloseHandle(hThread[i]);
	}

	printf("hello....\n");  //�߳̽�����ִ��
	system("pause");
	return;
}