// 华勤科技版权所有 2010-2011
// 
// 文件名：Track.h
// 功  能：页范围逻辑。
// 
// 作  者：MPF开发组
// 时  间：2011-07-02
// 
// ============================================================================

#ifndef _UITRACK_H_
#define _UITRACK_H_

#include <Framework/Controls/Thumb.h>
#include <Framework/Controls/RepeatButton.h>

namespace suic
{

/// <summary>
/// 实现Track控件
/// </summary>
class SUICORE_API Track : public FrameworkElement
{
public:

    static DpProperty* ValueProperty;
    static DpProperty* MaximumProperty;
    static DpProperty* MinimumProperty;

    static DpProperty* OrientationProperty;
    static DpProperty* ViewportSizeProperty;

    static DpProperty* IsDirectionReversedProperty;

    static bool StaticInit();

    Track();
    virtual ~Track();

    RTTIOfClass(Track)

    Float GetMaximum();
    void SetMaximum(Float val);

    Float GetMinimum();
    void SetMinimum(Float val);

    Float GetValue();
    void SetValue(Float val);

    Float GetThumbCenterOffset();
    void SetThumbCenterOffset(Float val);

    Float GetViewportSize();
    void SetViewportSize(Float val);

    int GetOrientation();
    void SetOrientation(int val);

    bool IsDirectionReversed();
    void SetIsDirectionReversed(bool val);
    
    Thumb* GetThumb();
    void SetThumb(Thumb* val);

    RepeatButton* GetDecreaseButton() const;
    void SetDecreaseButton(RepeatButton* val);

    RepeatButton* GetIncreaseButton() const;
    void SetIncreaseButton(RepeatButton* val);

public:

    virtual Float GetValueFromPoint(Point pt);
    virtual Float GetValueFromDistance(Float horizontal, Float vertical);

protected:

    void AddChild(Object* obj);
    int GetVisualChildrenCount();
    Element* GetVisualChild(int index);

    void OnPreApplyTemplate();

    bool OnReadingChild(IXamlNode* node);

    void OnArrange(const fSize& arrangeSize);
    fSize OnMeasure(const fSize& constraintSize);

private:

    void UpdateComponent(Element* oldValue, Element* newValue);
    void BindToTemplatedParent(DpProperty* target, DpProperty* source);
    void BindChildToTemplatedParent(FrameworkElement* element, DpProperty* target, DpProperty* source);

    void ComputeSliderLengths(fSize arrangeSize, bool isVertical, int& decreaseButtonLength, int& thumbLength, int& increaseButtonLength);
    bool ComputeScrollBarLengths(fSize arrangeSize, int viewportSize, bool isVertical, int& decreaseButtonLength, int& thumbLength, int& increaseButtonLength);

protected:

    Thumb* _thumb;

    RepeatButton* _decreaseButton;
    RepeatButton* _increaseButton;

    Float _density;
    Float _thumbCenterOffset;

    Element* _visualChildren[3];
};

inline Float Track::GetMaximum()
{
    return DpObject::GetValue(MaximumProperty)->ToFloat();
}

inline void Track::SetMaximum(Float val)
{
    if (!FloatUtil::AreClose(val, GetMaximum()))
    {
        DpObject::SetValue(MaximumProperty, new OFloat(val));
    }
}

inline Float Track::GetMinimum()
{
    return DpObject::GetValue(MinimumProperty)->ToFloat();
}

inline void Track::SetMinimum(Float val)
{
    DpObject::SetValue(MinimumProperty, new OFloat(val));
}

inline Float Track::GetValue()
{
    return DpObject::GetValue(ValueProperty)->ToFloat();
}

inline void Track::SetValue(Float val)
{
    if (!FloatUtil::AreClose(val, GetValue()))
    {
        DpObject::SetValue(ValueProperty, new OFloat(val));
    }
}

inline Float Track::GetThumbCenterOffset()
{
    return _thumbCenterOffset;
}

inline void Track::SetThumbCenterOffset(Float val)
{
    _thumbCenterOffset = val;
}

inline Float Track::GetViewportSize()
{
    return DpObject::GetValue(ViewportSizeProperty)->ToFloat();
}

inline void Track::SetViewportSize(Float val)
{
    DpObject::SetValue(ViewportSizeProperty, new Integer(val));
}

inline int Track::GetOrientation()
{
    return DpObject::GetValue(OrientationProperty)->ToInt();
}

inline void Track::SetOrientation(int val)
{
    if (val == Orientation::Horizontal)
    {
        DpObject::SetValue(OrientationProperty, OrientationBox::HorizontalBox);
    }
    else
    {
        DpObject::SetValue(OrientationProperty, OrientationBox::VerticalBox);
    }
}

inline bool Track::IsDirectionReversed()
{
    return DpObject::GetValue(IsDirectionReversedProperty)->ToInt() != 0;
}

inline void Track::SetIsDirectionReversed(bool val)
{
    DpObject::SetValue(IsDirectionReversedProperty, BOOLTOBOOLEAN(val));
}

inline Thumb* Track::GetThumb()
{
    return _thumb;
}

}

#endif
