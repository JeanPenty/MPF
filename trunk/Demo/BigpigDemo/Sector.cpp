#include "stdafx.h"
#include "Sector.h"

ImplementRTTIOfClass(Sector, suic::Shape)

DpProperty* Sector::StartPointProperty = NULL;
DpProperty* Sector::EndPointProperty   = NULL;

bool Sector::StaticInit()
{
	StartPointProperty = suic::DpProperty::Register("StartAngle", Sector::RTTIType(),suic::OFloat::RTTIType(), suic::DpPropMemory::GetPropMeta(NULL));
	EndPointProperty   = suic::DpProperty::Register("SweepAngle", Sector::RTTIType(),suic::OFloat::RTTIType(), suic::DpPropMemory::GetPropMeta(NULL));
	return true;
}

Sector::Sector(void)
{
}


Sector::~Sector(void)
{
}

//Size Sector::OnMeasure(const Size& size)
//{
//	return size;
//}

void Sector::OnRender(Drawing * drawing)
{
	drawing->Save();

	suic::Size rdSize = GetRenderSize();
	suic::fRect rcdc(0, 0, rdSize.cx, rdSize.cy);

	suic::Brush* fillBrush = this->GetFill();
	suic::Brush* strokeBrush = this->GetStroke();
	suic::Float  fThickness = this->GetStrokeThickness();

	suic::Pen pen;
	pen.SetBrush(strokeBrush);
	pen.SetThickness(fThickness);
	pen.SetAntiAlias(true);

	//drawing->DrawEllipse(fillBrush, &pen, rcdc);
	OFloat* pStart = (OFloat*)GetValue(StartPointProperty);
	Float fStartA = 60;//pStart->ToFloat();
	OFloat* pSweep = (OFloat*)GetValue(EndPointProperty);
	Float fSweepA = pSweep->ToFloat();

	if(fSweepA > 0.0)
		drawing->DrawArc(SolidColorBrush::Green, &pen, rcdc, fStartA, 36, true);

	drawing->Restore();
}