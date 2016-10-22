#include "stdafx.h"
#include "HwndHostButton.h"
#include "resource.h"
#include "BigpigDemo.h"

ImplementRTTIOfClass(HwndHostButton, suic::HwndHost)

DpProperty* HwndHostButton::ContentProperty = NULL;
DpProperty* HwndHostButton::IDProperty = NULL;

bool HwndHostButton::StaticInit()
{
	ContentProperty = suic::DpProperty::Register("Content", HwndHostButton::RTTIType(),suic::OString::RTTIType(), suic::DpPropMemory::GetPropMeta(NULL));
	IDProperty   = suic::DpProperty::Register("ID", HwndHostButton::RTTIType(),suic::Integer::RTTIType(), suic::DpPropMemory::GetPropMeta(NULL));
	
	return true;
}

HwndHostButton::HwndHostButton(void)
	:m_Handle(NULL)
	,m_font(NULL)
{
	m_font = CreateFont(16,
		0,
		0,
		0,
		FW_NORMAL,
		FALSE,
		FALSE,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		_T("Arial"));
}


HwndHostButton::~HwndHostButton(void)
{
	if(NULL != m_Handle)
	{
		DestroyWindow(m_Handle);
		m_Handle = NULL;
	}
	if(NULL != m_font)
	{
		DeleteObject(m_font);
		m_font = NULL;
	}
}

void HwndHostButton::OnLoaded(suic::LoadedEventArg* e)
{
	suic::HwndHost::OnLoaded(e);

	suic::VisualHost* pHost = RTTICast<suic::VisualHost>(e->GetTarget());
	if (NULL != pHost)
	{
		HWND hParent = HANDLETOHWND(pHost->GetHandle());
		if (::IsWindow(hParent))
		{
			//按钮文字
			OString* pContent = (OString*)GetValue(ContentProperty);
			String strContent = pContent->ToString();
			//按钮ID
			Integer* pID = (Integer*)GetValue(IDProperty);
			UINT nID = pID->ToInt();

			//创建按钮
			m_Handle = CreateWindowEx(WS_EX_WINDOWEDGE,
				WC_BUTTON,
				strContent.c_str(),
				WS_CHILDWINDOW|BS_DEFPUSHBUTTON|WS_VISIBLE|WS_CLIPSIBLINGS,
				0,0,0,0,	//位置和大小不需要
				hParent,
				(HMENU)nID,
				GetAppInstance(),
				NULL
				);

			if(NULL != m_Handle)
			{
				SendMessage(m_Handle,WM_SETFONT,(WPARAM)m_font,TRUE);
				Sethandle(HWNDTOHANDLE(m_Handle));
			}
		}
	}
}


void HwndHostButton::OnUnloaded(LoadedEventArg* e)
{
	suic::HwndHost::OnUnloaded(e);
    ::DestroyWindow(m_Handle);
}

void HwndHostButton::Dispose()
{
    ::DestroyWindow(m_Handle);
}