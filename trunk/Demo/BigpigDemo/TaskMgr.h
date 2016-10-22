#pragma once
#include "TaskData.h"
#include <map>

using namespace std;

class CTaskMgr
{
public:
	static CTaskMgr* GetInstance();
	~CTaskMgr(void);

	void Init();

	int AddTask(CTaskData* pData);

	void RunTask(int nID,int nType);

	void CancelTask(int nID);

	void RemoveTask(int nID);

	void ClickOK(int nID);

private:
	CTaskMgr(void);

	// 线程增加listbox的内容
	static DWORD WINAPI CreatTaskThread(LPVOID lpParameter);

	// 线程增删listbox临时内容
	static DWORD WINAPI RemoveTaskThread(LPVOID lpParameter);

	// 线程执行任务
	static DWORD WINAPI RunTaskThread(LPVOID lpParameter);

	struct CTaskInfo
	{
		int				m_nID;
		int				m_nType;	//1:正常 2:带提示 3:会出错
		bool			m_bRun;
		bool			m_bCancel;
		CTaskInfo()
			:m_nID(0)
			,m_nType(0)
			,m_bRun(false)
			,m_bCancel(false)
		{}
	};
	map<int,CTaskInfo*>		m_mapTaskInfos;
};

