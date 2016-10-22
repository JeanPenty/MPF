#pragma once
#include <Extend\suiwgxinc.h>
using namespace suic;

#define DeclarInt(name) \
	public: \
		int Get##name() \
		{ \
			return _##name; \
		} \
		void Set##name(int n) \
		{ \
			_##name = n; \
			NotifyChanged(""#name""); \
		} \
	private: \
		int _##name;

#define DeclarString(name) \
	public: \
	String Get##name() \
		{ \
		return _##name; \
		}; \
		void Set##name(String n) \
		{ \
		_##name = n; \
		NotifyChanged(""#name""); \
		}; \
	private: \
	String _##name;

#define AddConvert(name) {\
	static IBindConverter* s##name = new CBC##name(); \
	BindConverter::Ins()->Add(""#name"",s##name); \
}

struct InvokeParam : Object
{
	InvokeParam()
		:ptr(NULL)
	{
	}
	~InvokeParam()
	{
		if(NULL != ptr) delete ptr;
	}

	void*	ptr;
};