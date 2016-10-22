#pragma once
#include <Framework/Controls/Shape.h>

using namespace suic;

class Sector : public Shape
{
public:
	static DpProperty* StartPointProperty;
	static DpProperty* EndPointProperty;

	static bool StaticInit();

	Sector();
	virtual ~Sector();

	RTTIOfClass(Sector)

	Float GetStartPoint()
	{
		return GetValue(StartPointProperty)->ToFloat();
	};
	void SetStartPoint(Float val)
	{
		SetValue(StartPointProperty,new OFloat(val));
	};

	Float GetEndPoint()
	{
		return GetValue(EndPointProperty)->ToFloat();
	};
	void SetEndPoint(Float val)
	{
		SetValue(EndPointProperty,new OFloat(val));
	};

protected:

	//Size OnMeasure(const Size& size);
	void OnRender(Drawing * drawing);
};

