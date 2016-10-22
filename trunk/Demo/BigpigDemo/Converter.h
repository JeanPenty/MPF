// Converter

#pragma once

#include <Extend\suiwgxinc.h>
#include "UIHelp.h"
#include "TaskData.h"
using namespace suic;

//操作按钮是否显示 TaskState_Home
class CBCShowButtonBar : public IBindConverter
{
	AutoObj Convert(Object* inVal, String param)
	{
		int nValue = inVal->ToInt();
		return new Integer(nValue==TaskState_Home?Visibility::Visible:Visibility::Collapsed);
	};
	AutoObj ConvertBack(Object* inVal, String param)
	{
		return NULL;
	};
};

//进度栏是否显示 TaskState_Running TaskState_Waiting
class CBCShowStateBar : public IBindConverter
{
	AutoObj Convert(Object* inVal, String param)
	{
		int nValue = inVal->ToInt();
		AutoObj newThick = new Integer((nValue==TaskState_Running || nValue==TaskState_Waiting)?Visibility::Visible:Visibility::Collapsed);
		return newThick;
	};
	AutoObj ConvertBack(Object* inVal, String param)
	{
		return NULL;
	};
};

//任务信息是否显示 TaskState_Running
class CBCShowTaskInfo : public IBindConverter
{
	AutoObj Convert(Object* inVal, String param)
	{
		int nValue = inVal->ToInt();
		AutoObj newThick = new Integer(nValue==TaskState_Running?Visibility::Visible:Visibility::Collapsed);
		return newThick;
	};
	AutoObj ConvertBack(Object* inVal, String param)
	{
		AutoObj res;
		return res;
	};
};

//操作提示按钮是否显示 TaskState_Waiting
class CBCShowWaiting : public IBindConverter
{
	AutoObj Convert(Object* inVal, String param)
	{
		int nValue = inVal->ToInt();
		AutoObj newThick = new Integer(nValue==TaskState_Waiting?Visibility::Visible:Visibility::Collapsed);
		return newThick;
	};
	AutoObj ConvertBack(Object* inVal, String param)
	{
		AutoObj res;
		return res;
	};
};

//填写用户信息是否显示 TaskState_Input
class CBCShowInput : public IBindConverter
{
	AutoObj Convert(Object* inVal, String param)
	{
		int nValue = inVal->ToInt();
		AutoObj newThick = new Integer(nValue==TaskState_Input?Visibility::Visible:Visibility::Collapsed);
		return newThick;
	};
	AutoObj ConvertBack(Object* inVal, String param)
	{
		AutoObj res;
		return res;
	};
};

//重置按钮是否显示 TaskState_Finish
class CBCShowResetBtn : public IBindConverter
{
	AutoObj Convert(Object* inVal, String param)
	{
		int nValue = inVal->ToInt();
		AutoObj newThick = new Integer(nValue==TaskState_Finish?Visibility::Visible:Visibility::Collapsed);
		return newThick;
	};
	AutoObj ConvertBack(Object* inVal, String param)
	{
		AutoObj res;
		return res;
	};
};

//错误提示是否显示 TaskState_Error
class CBCShowError : public IBindConverter
{
	AutoObj Convert(Object* inVal, String param)
	{
		int nValue = inVal->ToInt();
		AutoObj newThick = new Integer(nValue==TaskState_Error?Visibility::Visible:Visibility::Collapsed);
		return newThick;
	};
	AutoObj ConvertBack(Object* inVal, String param)
	{
		return NULL;
	};
};

//任务类型提示
class CBCTaskTypeTip : public IBindConverter
{
	AutoObj Convert(Object* inVal, String param)
	{
		int nValue = inVal->ToInt();
		AutoObj obj = NULL;
		if (nValue == TaskType_1)
		{
			obj = new OString(L"正常任务");
		}
		else if (nValue == TaskType_2)
		{
			obj = new OString(L"弹出提示");
		}
		else if (nValue == TaskType_3)
		{
			obj = new OString(L"出现错误");
		}
		else if (nValue == TaskType_4)
		{
			obj = new OString(L"其他其他");
		}
		else if (nValue == TaskType_5)
		{
			obj = new OString(L"其他其他");
		}
		else if (nValue == TaskType_6)
		{
			obj = new OString(L"其他其他");
		}
		else if (nValue == TaskType_7)
		{
			obj = new OString(L"其他其他");
		}
		else if (nValue == TaskType_8)
		{
			obj = new OString(L"其他其他");
		}
		return obj;
	};
	AutoObj ConvertBack(Object* inVal, String param)
	{
		return NULL;
	};
};

//Info1Logo
class CBCInfo1Source : public IBindConverter
{
	AutoObj Convert(Object* inVal, String param)
	{
		String strValue = inVal->ToString();
		ResourceDictionary* rd = Application::Current()->GetResources();
		AutoObj obj = NULL;
		if (strValue.Equals(INFO1_SAMSUNG))
		{
			obj = rd->Lookup(L"LogoSamsung");
		}
		else if (strValue.Equals(INFO1_APPLE))
		{
			obj = rd->Lookup(L"LogoApple");
		}
		else if (strValue.Equals(INFO1_HUAWEI))
		{
			obj = rd->Lookup(L"LogoHuawei");
		}
		else
		{
			obj = rd->Lookup(L"LogoBlank");
		}
		return obj;
	};
	AutoObj ConvertBack(Object* inVal, String param)
	{
		return NULL;
	};
};

//Info3Logo
class CBCInfo3Source : public IBindConverter
{
	AutoObj Convert(Object* inVal, String param)
	{
		String strValue = inVal->ToString();
		ResourceDictionary* rd = Application::Current()->GetResources();
		AutoObj obj = NULL;
		if (strValue.Equals(INFO3_Android))
		{
			obj = rd->Lookup(L"Platform1");
		}
		else if (strValue.Equals(INFO3_Ios))
		{
			obj = rd->Lookup(L"Platform2");
		}
		else if (strValue.Equals(INFO3_WM))
		{
			obj = rd->Lookup(L"Platform3");
		}
		else
		{
			obj = rd->Lookup(L"Platform4");
		}
		return obj;
	};
	AutoObj ConvertBack(Object* inVal, String param)
	{
		return NULL;
	};
};

// 操作人类型输入选择
class CBCPhOwnerType : public IBindConverter
{
	AutoObj Convert(Object* inVal, String param)
	{
		String strPhOwnerType = inVal->ToString();
		if ((param == "1" && strPhOwnerType == "01")
		 || (param == "2" && strPhOwnerType == "02")
		 || (param == "3" && strPhOwnerType == "03")
			)
		{
			return Boolean::FromBool(true);
		}
		else
		{
			return Boolean::FromBool(false);
		}
		return NULL;
	}
	AutoObj ConvertBack(Object* inVal, String param)
	{
		bool bIsChecked = inVal->ToBool();
		AutoObj outVal = NULL;
		if(bIsChecked = true)
		{
			if (param == "1")
			{
				outVal = new OString(L"01");
			}
			else if(param == "2")
			{
				outVal = new OString(L"02");
			}
			else if(param == "3")
			{
				outVal = new OString(L"03");
			}
		}
		return outVal;
	}
};

class CBCProgressBarValue : public IBindConverter
{
	AutoObj Convert(Object* inVal, String param)
	{
		Float fProgress = inVal->ToFloat();
		Float fAngle = fProgress * 36;
		AutoObj res = new OFloat(fAngle);
		return res;
	};
	AutoObj ConvertBack(Object* inVal, String param)
	{
		return NULL;
	};
};

class CBCProgressBarText : public IBindConverter
{
	AutoObj Convert(Object* inVal, String param)
	{
		int nValue = inVal->ToInt();
		String strValue;
		strValue.Format(_U("%d"),nValue*10);
		strValue.Append(_U("%"),1);
		AutoObj res = new OString(strValue);
		return res;
	};
	AutoObj ConvertBack(Object* inVal, String param)
	{
		return NULL;
	};
};



void InitConverter()
{
	AddConvert(ShowButtonBar)
	AddConvert(ShowStateBar)
	AddConvert(ShowTaskInfo)
	AddConvert(ShowWaiting)
	AddConvert(ShowInput)
	AddConvert(ShowResetBtn)
	AddConvert(ShowError)

	AddConvert(TaskTypeTip)
	AddConvert(Info1Source)
	AddConvert(Info3Source)

	AddConvert(PhOwnerType)
	
	AddConvert(ProgressBarValue)
	AddConvert(ProgressBarText)
}