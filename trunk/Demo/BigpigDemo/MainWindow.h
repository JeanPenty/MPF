#pragma once
#include "TaskData.h"
#include <Extend/suiwgxinc.h>

using namespace suic;


enum
{
	WM_USER_BEGIN = 1000,
	WM_USER_ADDTASK,
	WM_USER_REMOVE,
	WM_USER_RUNNING,
	WM_USER_WATING,
	WM_USER_INPUT,
	WM_USER_FINISH,
	WM_USER_CANCEL
};

class CMainWindow : public suic::Window
{
public:

    CMainWindow(HWND hwnd);
	~CMainWindow();

	//void HostButton();

	// 线程刷新
	static suic::InvokeProxy* _reflesh;

private:
    void OnInitialized(suic::EventArg* e);
    void OnLoaded(suic::LoadedEventArg* e);
    // 创建自己的控件对象
    bool OnBuild(suic::IXamlNode* pNode, suic::ObjectPtr& obj);
    void OnConnect(suic::IXamlNode* pNode, suic::Object* target);

    bool OnEvent(Object* sender, MessageParam* mp);
	// 注册按钮响应
	void RegisterButtonEvent();
	// 按钮响应
	void OnButtonClicked(Element* sender, RoutedEventArg* e);
	// 消息回调
	void OnInvoker(suic::Object* sender, suic::InvokerArg* e);
	// ListBox选择事件
	void OnListBoxSelChanged(Element* sender, SelectionChangedEventArg* e);

	// ListBox
	void AddNewItem(CListboxItemData* pNewItem);
	void UpdateItem(CTaskData* pNewItem, int nFetchState);
	void RemoveItem(int nID);

private:
	HWND m_hWnd;
	ObservableCollection *m_pListBoxData;
	suic::Mutex m_mutex;

	suic::StackPanel*				m_pCenterControl;
	suic::PlayBox*					m_pPlayBox;
};

