#pragma once
#include <Framework/Controls/HwndHost.h>

using namespace suic;

class HwndHostButton : public HwndHost
{
public:
	static DpProperty* ContentProperty;
	static DpProperty* IDProperty;

	static bool StaticInit();

	HwndHostButton(void);
	~HwndHostButton(void);

	RTTIOfClass(HwndHostButton)

protected:

    void Dispose();
	void OnLoaded(LoadedEventArg* e);
	void OnUnloaded(LoadedEventArg* e);

private:
	HWND m_Handle;
	HFONT m_font;
};

