#include "StdAfx.h"
#include "TaskMgr.h"
#include "MainWindow.h"

string strInfo1[4] = {INFO1_SAMSUNG,INFO1_APPLE,INFO1_HUAWEI,"other"};
string strInfo3[4] = {INFO3_Android,INFO3_Ios,INFO3_WM,"other"};

CTaskMgr::CTaskMgr(void)
{
}


CTaskMgr::~CTaskMgr(void)
{
}

CTaskMgr* CTaskMgr::GetInstance()
{
	static CTaskMgr m_Instance;
	return &m_Instance;
}

void CTaskMgr::Init()
{
	HANDLE hTaskThread = CreateThread(NULL,0,CreatTaskThread, (LPVOID)this, 0, NULL);
	CloseHandle(hTaskThread);
}

DWORD CTaskMgr::CreatTaskThread(LPVOID lpParameter)
{
	CTaskMgr* pTask = (CTaskMgr*)lpParameter;

	Sleep(3000);
	int nNum = 0;
	while (true)
	{
		CTaskData* pData = new CTaskData();
		pData->m_strInfo1 = strInfo1[nNum];
		pData->m_strInfo2 = "从线程添加的item";
		pData->m_strInfo3 = strInfo3[nNum];

		++nNum;
		if(nNum == 4)nNum=0;

		int nID = pTask->AddTask(pData);
		if(nID == 50)
			break;

		Sleep(2000);
	}
	return 0;
}

DWORD CTaskMgr:: RemoveTaskThread(LPVOID lpParameter)
{
	CTaskMgr* pTask = (CTaskMgr*)lpParameter;


	int nID = 2;

	while(true)
	{
		pTask->RemoveTask(++nID);
		Sleep(2000);

		if(nID == 50)
		{
			pTask->RemoveTask(1);
			pTask->RemoveTask(2);
			break;
		}
	}

	return 0;
}

int CTaskMgr::AddTask(CTaskData* pData)
{
	static int nNum = 0;
	nNum++;
	pData->m_nID = nNum;
	char szInfo2[10] = {0};
	sprintf_s(szInfo2,": %d", nNum);
	pData->m_strInfo2 += szInfo2;

	if(nNum == 10)
	{
		HANDLE hTaskThread = CreateThread(NULL,0,RemoveTaskThread,(LPVOID)this, 0, NULL);
		CloseHandle(hTaskThread);
	}

	CTaskInfo* pInfo = new CTaskInfo();
	pInfo->m_nID = nNum;
	m_mapTaskInfos.insert(make_pair(nNum, pInfo));

	InvokeParam* pParam = new InvokeParam();
	pParam->ref();
	pParam->ptr = pData;
	if(NULL!=CMainWindow::_reflesh)
		CMainWindow::_reflesh->PostInvoker(WM_USER_ADDTASK, pParam);

	return nNum;
}

void CTaskMgr::RunTask(int nID,int nType)
{
	auto it = m_mapTaskInfos.find(nID);
	if (it == m_mapTaskInfos.end())
	{
		return;
	}

	CTaskInfo* pTask = it->second;
	pTask->m_nType = nType;

	HANDLE hTaskThread = CreateThread(NULL,0,RunTaskThread, (LPVOID)pTask, 0, NULL);
	CloseHandle(hTaskThread);
	
}

DWORD CTaskMgr::RunTaskThread(LPVOID lpParameter)
{
	CTaskInfo* pTask = (CTaskInfo*)lpParameter;
	pTask->m_bRun = true;
	pTask->m_bCancel = false;
	for (int i=0; i<20; ++i)
	{
		if(pTask->m_bCancel)
		{
			break;
		}

		if(i==10) //任务执行到一半时
		{
			if(pTask->m_nType == 2)	//等待用户点击确认
			{
				CTaskData* pData = new CTaskData();
				pData->m_nID = pTask->m_nID;
				pData->m_get = i;
				pData->m_total = 20;
				pData->m_eventStr = "点击确认或取消";

				//向界面发送信息
				InvokeParam* pParam = new InvokeParam();
				pParam->ref();
				pParam->ptr = pData;
				CMainWindow::_reflesh->PostInvoker(WM_USER_WATING, (Object*)pParam);

				while(pTask->m_nType == 2)
				{
					Sleep(500);
				}
				continue;
			}
			else if (pTask->m_nType == 3)	//出错了
			{
				CTaskData* pData = new CTaskData();
				pData->m_nID = pTask->m_nID;
				pData->m_get = i;
				pData->m_total = 20;
				pData->m_eventStr = "出错了";
				pData->m_errStr = "出错了haha";
				pData->m_errCode = 1;

				//向界面发送信息
				InvokeParam* pParam = new InvokeParam();
				pParam->ref();
				pParam->ptr = pData;
				CMainWindow::_reflesh->PostInvoker(WM_USER_INPUT, (Object*)pParam);

				break;
			}
		}

		CTaskData* pData = new CTaskData();
		pData->m_nID = pTask->m_nID;
		pData->m_get = i;
		pData->m_total = 20;
		char szInfo[100] = {0};
		sprintf_s(szInfo,"任务信息%d",i);
		pData->m_eventStr = szInfo;
		memset(szInfo,0,100);
		sprintf_s(szInfo,"错误信息%d",i);
		pData->m_errStr = szInfo;
		memset(szInfo,0,100);
		sprintf_s(szInfo,"详细信息%d",i);
		pData->m_eventMore = szInfo;

		//向界面发送信息
		InvokeParam* pParam = new InvokeParam();
		pParam->ref();
		pParam->ptr = pData;
		CMainWindow::_reflesh->PostInvoker(WM_USER_RUNNING, (Object*)pParam);

		Sleep(1000);
	}

	// 执行结束
	if(pTask->m_nType != 3)
	{
		if (!pTask->m_bCancel)
		{
			//任务完成 向界面发送信息
			CTaskData* pData = new CTaskData();
			pData->m_nID = pTask->m_nID;
			InvokeParam* pParam = new InvokeParam();
			pParam->ref();
			pParam->ptr = pData;
			CMainWindow::_reflesh->PostInvoker(WM_USER_INPUT, (Object*)pParam);
		}
		else
		{
			// 任务取消 向界面发送信息
			CTaskData* pData = new CTaskData();
			pData->m_nID = pTask->m_nID;
			InvokeParam* pParam = new InvokeParam();
			pParam->ref();
			pParam->ptr = pData;
			CMainWindow::_reflesh->PostInvoker(WM_USER_CANCEL, (Object*)pParam);
		}
	}

	pTask->m_bRun = false;
	return 0;
}

void CTaskMgr::CancelTask(int nID)
{
	auto it = m_mapTaskInfos.find(nID);
	if (it == m_mapTaskInfos.end())
	{
		return;
	}
	CTaskInfo* pTask = it->second;
	pTask->m_bCancel = true;
}

void CTaskMgr::RemoveTask(int nID)
{
	auto it = m_mapTaskInfos.find(nID);
	if (it == m_mapTaskInfos.end())
	{
		return;
	}
	CTaskInfo* pTask = it->second;

	// 任务不在执行时才能移除
	pTask->m_bCancel = true;
	while (pTask->m_bRun)
	{
		Sleep(1000);
	}
	
	//向界面发送信息
	int* nPhoneID = new int;
	*nPhoneID = it->first;
	InvokeParam* pParam = new InvokeParam();
	pParam->ref();
	pParam->ptr = nPhoneID;
	CMainWindow::_reflesh->PostInvoker(WM_USER_REMOVE, (Object*)pParam);

	m_mapTaskInfos.erase(it);
}

void CTaskMgr::ClickOK(int nID)
{
	auto it = m_mapTaskInfos.find(nID);
	if (it == m_mapTaskInfos.end())
	{
		return;
	}
	CTaskInfo* pTask = it->second;

	pTask->m_nType = 1;
}