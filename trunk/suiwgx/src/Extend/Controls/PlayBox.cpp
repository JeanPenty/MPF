// ======================================================================
//
// Copyright (c) 2008-2012 Inc. All rights reserved.
//
// ���ߣ�����
// ���䣺china0851@foxmail.com
//
// ======================================================================

//////////////////////////////////////////////////////////////////////////////
// PlayBox.cpp

//#include "stdafx.h"

#include <Extend/Controls/PlayBox.h>
#include <Framework/Animation/AnimationAsKeyFrame.h>

namespace suic
{

ImplementRTTIOfClass(PlayBox, suic::FrameworkElement)

suic::DpProperty* PlayBox::BackgroundProperty;
suic::DpProperty* PlayBox::PlayProperty;
suic::DpProperty* PlayBox::PlayIndexProperty;
suic::DpProperty* PlayBox::PlayBehaviorProperty;
suic::DpProperty* PlayBox::MousePlayProperty;
suic::DpProperty* PlayBox::ShowFrameProperty;

suic::DpProperty* PlayBox::PlayDelayProperty;

PlayBox::PlayBox()
    : _elemColl(NULL)
    , _isReverse(false)
{
    PlayBox::StaticInit();
}

PlayBox::~PlayBox()
{
    if (NULL != _elemColl)
    {
        _elemColl->Clear();
        delete _elemColl;
    }
}

void PlayBox::OnPlayIndexPropChanged(suic::DpObject* d, suic::DpPropChangedEventArg* e)
{

}

void PlayBox::OnPlayPropChanged(suic::DpObject* d, suic::DpPropChangedEventArg* e)
{
    PlayBox* playBox = suic::RTTICast<PlayBox>(d);
    if (e->GetNewValue()->ToBool())
    {
        playBox->Play();
    }
    else
    {
        playBox->BeginAnimation(PlayIndexProperty, NULL);
    }
}

bool PlayBox::StaticInit()
{
    if (NULL == BackgroundProperty)
    {
        BackgroundProperty = suic::DpProperty::Register(_U("Background"), RTTIType(), suic::Brush::RTTIType(), 
            suic::DpPropMemory::GetPropMeta(NULL, suic::PropMetadataOptions::AffectsRender));
        PlayIndexProperty = suic::DpProperty::Register(_U("PlayIndex"), RTTIType(), suic::Integer::RTTIType(), 
            suic::DpPropMemory::GetPropMeta(suic::Integer::GetNegInt(1), suic::PropMetadataOptions::AffectsRender, &PlayBox::OnPlayIndexPropChanged));
        PlayProperty = suic::DpProperty::Register(_U("Play"), RTTIType(), suic::Boolean::RTTIType(), 
            suic::DpPropMemory::GetPropMeta(suic::Boolean::False, suic::PropMetadataOptions::AffectsRender, &PlayBox::OnPlayPropChanged));

        PlayBehaviorProperty = suic::DpProperty::Register(_U("PlayBehavior"), RTTIType(), suic::Integer::RTTIType(), 
            suic::DpPropMemory::GetPropMeta(suic::Integer::GetPosInt(2), suic::PropMetadataOptions::AffectsRender));
        MousePlayProperty = suic::DpProperty::Register(_U("MousePlay"), RTTIType(), suic::Boolean::RTTIType(), 
            suic::DpPropMemory::GetPropMeta(suic::Boolean::False, suic::PropMetadataOptions::AffectsRender));
        ShowFrameProperty = suic::DpProperty::Register(_U("ShowFrame"), RTTIType(), suic::Boolean::RTTIType(), 
            suic::DpPropMemory::GetPropMeta(suic::Boolean::True, suic::PropMetadataOptions::AffectsRender));

        PlayDelayProperty = suic::DpProperty::RegisterAttached(_U("PlayDelay"), RTTIType(), suic::Integer::RTTIType(), 
            suic::DpPropMemory::GetPropMeta(new suic::Integer(100), suic::PropMetadataOptions::AffectsRender));
    }

    return true;
}

int PlayBox::GetPlayIndex()
{
    return GetValue(PlayIndexProperty)->ToInt();
}

void PlayBox::SetPlayIndex(int val)
{
    SetValue(PlayIndexProperty, new suic::Integer(val));
}

int PlayBox::GetPlayDelay(suic::Element* elem)
{
    return elem->GetValue(PlayDelayProperty)->ToInt();
}

void PlayBox::SetPlayDelay(suic::Element* elem, int val)
{
    elem->SetValue(PlayDelayProperty, new suic::Integer(val));
}

bool PlayBox::GetShowFrame()
{
    return GetValue(ShowFrameProperty)->ToBool();
}

void PlayBox::SetShowFrame(bool val)
{
    SetValue(ShowFrameProperty, BOOLTOBOOLEAN(val));
}

bool PlayBox::GetPlay()
{
    return GetValue(PlayProperty)->ToBool();
}

void PlayBox::SetPlay(bool val)
{
    SetValue(PlayProperty, BOOLTOBOOLEAN(val));
}

bool PlayBox::GetMousePlay()
{
    return GetValue(MousePlayProperty)->ToBool();
}

void PlayBox::SetMousePlay(bool val)
{
    SetValue(MousePlayProperty, BOOLTOBOOLEAN(val));
}

int PlayBox::GetPlayBehavior()
{
    return GetValue(PlayBehaviorProperty)->ToInt();
}

void PlayBox::SetPlayBehavior(int val)
{
    SetValue(PlayBehaviorProperty, suic::Integer::GetPosInt(val));
}

suic::Brush* PlayBox::GetBackground()
{
    return suic::RTTICast<suic::Brush>(GetValue(BackgroundProperty));
}

void PlayBox::SetBackground(suic::Brush* val)
{
    SetValue(BackgroundProperty, val);
}

suic::ElementColl* PlayBox::GetChildCollection()
{
    if (NULL == _elemColl)
    {
        _elemColl = new suic::ElementColl(this, this);
    }
    return _elemColl;
}

void PlayBox::AddChild(suic::Object* child)
{
    if (child != NULL)
    {
        child->ref();
        suic::Element* elem = suic::RTTICast<suic::Element>(child);
        GetChildCollection()->Add(elem);
        child->unref();
    }
}

void PlayBox::AddText(suic::String val)
{
    
}

void PlayBox::RemoveChild(Object* child)
{
    if (NULL == _elemColl)
    {
        Element* pElem = RTTICast<Element>(child);
        _elemColl->Remove(pElem);
    }
}

int PlayBox::GetVisualChildrenCount()
{
    if (GetShowFrame() && _elemColl && 
        _elemColl->GetCount() > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

suic::Element* PlayBox::GetVisualChild(int i)
{
    int index = GetCurrentIndex();
    if (index >= 0)
    {
        return _elemColl->GetAt(index);
    }
    else
    {
        return NULL;
    }
}

suic::Element* PlayBox::GetLogicalChild(int index)
{
    return GetVisualChild(index);
}

int PlayBox::GetLogicalChildrenCount()
{
    return GetVisualChildrenCount();
}

suic::fSize PlayBox::OnMeasure(const suic::fSize& constraint)
{
    suic::fSize measureSize;

    if (GetShowFrame() && _elemColl != NULL)
    {
        for (int i = 0; i < _elemColl->GetCount(); ++i)
        {
            suic::Element* child = _elemColl->GetAt(i);

            if (child != NULL)
            {
                MeasureChild(child, constraint);
                //child->Measure(constraint);
                suic::fSize size = child->GetDesiredSize();
                measureSize.cx = Math::Max(measureSize.cx, size.cx);
                measureSize.cy = Math::Max(measureSize.cy, size.cy);
            }
        }
    }

    return measureSize;
}

void PlayBox::OnArrange(const suic::fSize& arrangeSize)
{
    if (GetShowFrame() && NULL != _elemColl && _elemColl->GetCount() > 0)
    {
        for (int i = 0; i < _elemColl->GetCount(); ++i)
        {
            suic::Element* child = _elemColl->GetAt(i);

            if (child != NULL)
            {
                suic::fRect rect(0, 0, arrangeSize.cx, arrangeSize.cy);
                child->Arrange(rect);
            }
        }
    }
}

void PlayBox::OnRender(suic::Drawing * drawing)
{
    suic::Brush* background(GetBackground());

    if (background != NULL)
    {
        suic::fSize rSize = GetRenderSize();
        suic::fRect rect(suic::fPoint(), rSize);
        drawing->DrawRect(background, NULL, rect);
    }
}

void PlayBox::OnMouseEnter(suic::MouseButtonEventArg* e)
{
    suic::FrameworkElement::OnMouseEnter(e);
    if (GetMousePlay())
    {
        BeginAnimation(PlayIndexProperty, NULL);
        _isReverse = false;
        Play();
    }
}

void PlayBox::OnMouseLeave(suic::MouseButtonEventArg* e)
{
    suic::FrameworkElement::OnMouseLeave(e);
    if (GetMousePlay())
    {
        BeginAnimation(PlayIndexProperty, NULL);
        _isReverse = true;
        Play();
    }
}

void PlayBox::OnInitialized(suic::EventArg* e)
{
    FrameworkElement::OnInitialized(e);
}

void PlayBox::OnLoaded(suic::LoadedEventArg* e)
{
    FrameworkElement::OnLoaded(e);    
    if (_elemColl != NULL)
    {
        _elemColl->CheckLoaded(e);
    }

    if (GetPlay())
    {
        Play();
    }
}

int PlayBox::GetCurrentIndex()
{
    int index = -1;

    if (NULL != _elemColl && _elemColl->GetCount() > 0)
    {
        index = GetPlayIndex();
        if (_isReverse)
        {
            index = _elemColl->GetCount() - index - 1;
        }

        if (index < 0 || index >= _elemColl->GetCount())
        {
            index = 0;
        }
    }

    return index;
}

void PlayBox::Play()
{
    if (_elemColl != NULL && IsEnabled())
    {
        int i = 0;
        int iDuration = 0;
        int iCount = _elemColl->GetCount();
        suic::Int32AnimationUsingKeyFrame* aniFrame = NULL;

        SetPlayIndex(0);
        aniFrame = new suic::Int32AnimationUsingKeyFrame();

        for (i = 0; i < iCount; ++i)
        {
            int index = _isReverse ? iCount - i - 1 : i;
            Element* child = GetVisualChild(index);

            if (child != NULL)
            {
                iDuration += GetPlayDelay(child);
                suic::KeyTime kt(iDuration, suic::KeyTimeType::TimeSpan);
                suic::LinearInt32KeyFrame* keyItem = new suic::LinearInt32KeyFrame(kt, i);
                aniFrame->AddChild(keyItem);
            }
        }

        suic::Duration duration(iDuration);
        aniFrame->SetDuration(duration);

        suic::RepeatBehavior rb;

        if (!GetMousePlay())
        {
            int iBehavior = GetPlayBehavior();
            rb.type = suic::RepeatBehavior::Type::Forever;
            if (iBehavior >= 0 && iBehavior <= 2)
            {
                rb.type = (suic::RepeatBehavior::Type)(iBehavior);
            }
        }

        rb.duration = iDuration;
        aniFrame->SetRepeatBehavior(rb);
        BeginAnimation(PlayIndexProperty, aniFrame);
    }
}

}
