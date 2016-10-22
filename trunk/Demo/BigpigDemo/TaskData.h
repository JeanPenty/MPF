#pragma once

#include "UIHelp.h"
#include <string>

//任务类型
enum eTaskType
{
	TaskType_None = 0,
	TaskType_1,
	TaskType_2,
	TaskType_3,
	TaskType_4,
	TaskType_5,
	TaskType_6,
	TaskType_7,
	TaskType_8
};

//任务状态
enum eTaskState
{
	TaskState_Home = 0,			//起始状态
	TaskState_Running,			//正在执行
	TaskState_Waiting,			//等待界面确认
	TaskState_Input,			//任务完成，输入信息
	TaskState_Finish,			//填写信息完成
	TaskState_Error				//失败了
};

//Info1
#define INFO1_SAMSUNG "Samsung"
#define INFO1_APPLE "Apple"
#define INFO1_HUAWEI "Huawei"

//Info3
#define INFO3_Android "Android"
#define INFO3_Ios "IOS"
#define INFO3_WM "wm"


class CListboxItemData : public NotifyPropChanged
{
public:
	BeginMember(CListboxItemData, NotifyPropChanged)
		MemberInt(ID)
		MemberInt(TaskType)
		MemberInt(TaskState)
		MemberInt(Percent)
		MemberString(Info1)
		MemberString(Info2)
		MemberString(Info3)
		MemberString(OwnerType)
		MemberString(OwnerName)
		MemberString(OwnerNum)
		MemberString(OwnerPhone)
		MemberInt(EventCode)
		MemberString(EventStr)
		MemberString(EventMore)
		MemberInt(ErrCode)
		MemberString(ErrStr)
	EndMember()

	CListboxItemData()
	{
		_TaskType = TaskType_None;
		_TaskState = TaskState_Home;
		_Percent = 0;
		_OwnerType = "01";
	}
	~CListboxItemData()
	{
	}

	void Reset()
	{
		SetOwnerType("01");
		SetOwnerName("");
		SetOwnerNum("");
		SetOwnerPhone("");
		SetEventCode(0);
		SetEventStr("");
		SetErrCode(0);
		SetErrStr("");
		SetEventMore("");
	}

	DeclarInt(ID)			//手机ID
	DeclarInt(TaskType)		//任务类型 eTaskType
	DeclarInt(TaskState)	//任务状态 eTaskState
	DeclarInt(Percent)		//任务进度
	DeclarString(Info1)		//展示信息
	DeclarString(Info2)		//展示信息
	DeclarString(Info3)		//展示信息
	DeclarString(OwnerType)	//操作人类型
	DeclarString(OwnerName) //操作人姓名
	DeclarString(OwnerNum)	//操作人证件号码
	DeclarString(OwnerPhone)//操作手机号
	DeclarInt(EventCode)	//任务提示
	DeclarString(EventStr)	//任务提示
	DeclarString(EventMore) //任务详细提示
	DeclarInt(ErrCode)		//错误信息
	DeclarString(ErrStr)	//错误信息

};

struct CTaskData
{
	int				m_nID;
	std::string		m_strInfo1;
	std::string		m_strInfo2;
	std::string		m_strInfo3;
	int				m_eventType;
	std::string		m_eventStr;
	std::string		m_eventMore;
	int				m_errCode;
	std::string		m_errStr;
	int				m_total;
	int				m_get;

	CTaskData()
		:m_nID(0)
		,m_eventType(0)
		,m_errCode(0)
		,m_get(-1)
		,m_total(-1)
	{
	}
};