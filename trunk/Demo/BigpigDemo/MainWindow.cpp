
#include "stdafx.h"
#include "MainWindow.h"
#include "TaskMgr.h"
#include "UIHelp.h"
#include "BigPigDemo.h"

suic::InvokeProxy* CMainWindow::_reflesh = NULL;

CMainWindow::CMainWindow(HWND hwnd)
	:m_pCenterControl(NULL)
	,m_pPlayBox(NULL)
{
	m_pListBoxData = new ObservableCollection();
	m_pListBoxData->ref();
	m_hWnd = hwnd;
}

CMainWindow::~CMainWindow()
{
	m_pListBoxData->unref();
}

bool CMainWindow::OnBuild(suic::IXamlNode* pNode, suic::ObjectPtr& obj)
{
    return false;
}

void CMainWindow::OnConnect(suic::IXamlNode* pNode, suic::Object* target)
{
    
}

void CMainWindow::OnInitialized(suic::EventArg* e)
{
    suic::Window::OnInitialized(e);

	//Invoke初始化
	_reflesh = new suic::InvokeProxy(this);
	_reflesh->ref();
	_reflesh->Invoker+=suic::InvokerHandler(this, &CMainWindow::OnInvoker);

	//左边列表
	suic::ListBox* fetchlistbox = FindElem<suic::ListBox>(_U("MyList"));
	if (NULL != fetchlistbox)
	{
		fetchlistbox->SetItemsSource(m_pListBoxData);

		fetchlistbox->AddSelectionChanged(new SelectionChangedEventHandler(this, &CMainWindow::OnListBoxSelChanged));
	}

	//中间详细信息
	m_pCenterControl = FindElem<suic::StackPanel>(_U("CenterInfo"));
}

void CMainWindow::OnLoaded(suic::LoadedEventArg* e)
{
    suic::Window::OnLoaded(e);

    // 窗口居中
    //CenterWindow();

    // 注册按钮事件处理
    RegisterButtonEvent();
    
	CTaskMgr* pTaskMgr = CTaskMgr::GetInstance();
	pTaskMgr->Init();
}

//void CMainWindow::HostButton()
//{
//	suic::HwndHost* pHH1 = FindElem<suic::HwndHost>(_U("host1"));
//	if (NULL != pHH1)
//	{
//		HWND hwndButton = CreateWindowEx(0/*WS_EX_WINDOWEDGE*/,
//			WC_BUTTON,
//			_T("按钮"),
//			WS_CHILDWINDOW|BS_DEFPUSHBUTTON|WS_VISIBLE|WS_CLIPSIBLINGS,
//			0,0,0,0,	//位置和大小不需要
//			m_hWnd,
//			(HMENU)BUTTON_ID_TEST,
//			GetAppInstance(),
//			NULL
//			);
//		pHH1->Sethandle(HWNDTOHANDLE(hwndButton));
//	}
//}

bool CMainWindow::OnEvent(Object* sender, MessageParam* mp)
{
	if (mp->message == WM_COMMAND)
	{
		if (10001 == mp->wp)
		{
			return true;
		}
		else if (10002 == mp->wp)
		{
			return true;
		}
		else if (10003 == mp->wp)
		{
			return true;
		}
		else if (20001 == mp->wp)
		{
			return true;
		}
		return false;
	}
	else
	{
		return false;
	}
}

void CMainWindow::RegisterButtonEvent()
{
	// 注册路由事件
	Window* win = DynamicCast<Window>(FindName(_U("window")));
	if (NULL != win)
	{
		win->AddHandler(Button::ClickEvent, new ClickEventHandler(this, &CMainWindow::OnButtonClicked));
	}
}

void CMainWindow::AddNewItem(CListboxItemData* pNewItem)
{
	m_pListBoxData->AddItem(pNewItem);
}

void CMainWindow::UpdateItem(CTaskData* pNewItem, int nTaskState)
{
	suic::UIGuard<suic::Mutex> sunc(m_mutex);
	int nID = pNewItem->m_nID;
	CListboxItemData* pItem = NULL;
	int nCount = m_pListBoxData->GetCount();
	for (int i = 0; i<nCount; ++i)
	{
		pItem = (CListboxItemData*)(m_pListBoxData->GetItem(i));
		if (pItem->GetID() == nID)
		{
			int nTaskType = pItem->GetTaskType();

			// 计算进度
			int nPercent = 0;
			if(pNewItem->m_get>=0 && pNewItem->m_total>0)
			{
				nPercent = pNewItem->m_get*100/pNewItem->m_total;
			}

			pItem->SetTaskState(nTaskState);						//获取状态
			pItem->SetPercent(nPercent);							//进度
			pItem->SetEventCode(pNewItem->m_eventType);				//当前任务
			pItem->SetEventStr(pNewItem->m_eventStr.c_str());		//当前任务
			pItem->SetErrCode(pNewItem->m_errCode);					//错误信息
			pItem->SetErrStr(pNewItem->m_errStr.c_str());			//错误信息
			pItem->SetEventMore(pNewItem->m_eventMore.c_str());		//详细信息

			if(TaskState_Input == nTaskState)
			{
				// 任务完成，进度设为100
				nPercent = 100;
				pItem->SetPercent(nPercent);

				if (0 != pNewItem->m_errCode)
				{//失败
					pItem->SetTaskState(TaskState_Error);
				}
			}

			break;
		}// if GetID = ID
	}// for All Item
}

void CMainWindow::RemoveItem(int nID)
{
	suic::UIGuard<suic::Mutex> sunc(m_mutex);
	CListboxItemData* pItem = NULL;
	int nCount = m_pListBoxData->GetCount();
	for (int i = 0; i<nCount; ++i)
	{
		pItem = (CListboxItemData*)(m_pListBoxData->GetItem(i));
		if (pItem->GetID() == nID)
		{
			m_pListBoxData->RemoveItemAt(i);
			break;
		}
	}
}

void CMainWindow::OnInvoker(suic::Object* sender, suic::InvokerArg* e)
{
	suic::UIGuard<suic::Mutex> sunc(m_mutex);
	int nWhat = e->GetWhat();
	Object* pObj = e->GetData();

	if (WM_USER_ADDTASK == nWhat)
	{
		InvokeParam* pParam = (InvokeParam*)pObj;
		CTaskData* pData = (CTaskData*)(pParam->ptr);
		
		CListboxItemData* newItemData = new CListboxItemData();
		newItemData->SetID(pData->m_nID);
		newItemData->SetInfo1(pData->m_strInfo1.c_str());
		newItemData->SetInfo2(pData->m_strInfo2.c_str());
		newItemData->SetInfo3(pData->m_strInfo3.c_str());
		AddNewItem(newItemData);
		pParam->unref();
	}
	else if(WM_USER_REMOVE == nWhat)
	{
		InvokeParam* pParam = (InvokeParam*)pObj;
		int* nPhoneID = (int*)(pParam->ptr);
		RemoveItem(*nPhoneID);
		pParam->unref();
	}
	else if(WM_USER_RUNNING == nWhat)
	{
		InvokeParam* pParam = (InvokeParam*)pObj;
		CTaskData* pData = (CTaskData*)(pParam->ptr);
		UpdateItem(pData, TaskState_Running);
		pParam->unref();
	}
	else if (WM_USER_WATING == nWhat)
	{
		InvokeParam* pParam = (InvokeParam*)pObj;
		CTaskData* pData = (CTaskData*)(pParam->ptr);
		UpdateItem(pData, TaskState_Waiting);
		pParam->unref();
	}
	else if(WM_USER_INPUT == nWhat)
	{
		InvokeParam* pParam = (InvokeParam*)pObj;
		CTaskData* pData = (CTaskData*)(pParam->ptr);
		UpdateItem(pData, TaskState_Input);
		pParam->unref();
	}
	else if(WM_USER_CANCEL == nWhat)
	{
		InvokeParam* pParam = (InvokeParam*)pObj;
		CTaskData* pMsgNode = (CTaskData*)(pParam->ptr);
		UpdateItem(pMsgNode, TaskState_Home);
		pParam->unref();
	}
}

void CMainWindow::OnButtonClicked(Element* sender, RoutedEventArg* e)
{
	Element* btn = DynamicCast<Element>(e->GetOriginalSource());
	if(btn == nullptr)return;

	suic::Object* pItem = btn->GetDataContext();
	CListboxItemData* pItemData = (CListboxItemData*)pItem;
	if(pItemData == nullptr)return;

	CTaskMgr* pTaskMgr = CTaskMgr::GetInstance();
	if(pTaskMgr == nullptr)return;

	String strName = btn->GetName();
	if (strName.Equals(_U("btnTask1")))		//正常执行任务
	{
		pItemData->SetTaskType(TaskType_1);
		pTaskMgr->RunTask(pItemData->GetID(),1);
		e->SetHandled(true);
	}
	else if (strName.Equals(_U("btnTask2")))	// 任务中弹出提示
	{
		pItemData->SetTaskType(TaskType_2);
		pTaskMgr->RunTask(pItemData->GetID(),2);
		e->SetHandled(true);
	}
	else if (strName.Equals(_U("btnTask3")))	// 任务会出错
	{
		pItemData->SetTaskType(TaskType_3);
		pTaskMgr->RunTask(pItemData->GetID(),3);
		e->SetHandled(true);
	}
	else if (strName.Equals(_U("btnTask4")))	//其他
	{
		//pItemData->SetTaskType(TaskType_4);
		//pTaskMgr->RunTask(pItemData->GetID(),1);
		e->SetHandled(true);
	}
	else if (strName.Equals(_U("Cancel")))		// 取消任务
	{
		pTaskMgr->CancelTask(pItemData->GetID());
		pItemData->Reset();
		pItemData->SetEventStr("正在取消");
		e->SetHandled(true);
	}
	else if (strName.Equals(_U("WaitingMsgOK")))// 提示信息 确认/继续
	{
		pTaskMgr->ClickOK(pItemData->GetID());
		e->SetHandled(true);
	}
	else if (strName.Equals(_U("WaitingMsgCancel")))// 提示信息 取消/跳过
	{
		pTaskMgr->ClickOK(pItemData->GetID());
		e->SetHandled(true);
	}
	else if (strName.Equals(_U("UserInfo_OK")))		//用户信息填写完成
	{
		pItemData->SetTaskState(TaskState_Finish);
		e->SetHandled(true);
	}
	else if (strName.Equals(_U("Reset"))|| strName.Equals(_U("Return")))	// 重置
	{
		pItemData->SetTaskState(TaskState_Home);
		pItemData->Reset();
		e->SetHandled(true);
	}
}

void CMainWindow::OnListBoxSelChanged(Element* sender, SelectionChangedEventArg* e)
{
	String str = sender->GetName();
	int nSel = e->GetAddedItems()->GetCount();
	if (nSel > 0)
	{
		Object* p = e->GetAddedItems()->GetItem(0);
		CListboxItemData* pData = RTTICast<CListboxItemData>(p);

		if (NULL != m_pCenterControl && NULL != pData)
		{
			m_pCenterControl->SetDataContext(pData);
		}
	}
	e->SetHandled(true);
}