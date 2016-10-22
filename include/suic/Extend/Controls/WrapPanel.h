// 华勤科技版权所有 2010-2011
// 
// 文件名：WrapPanel.h
// 功  能：换行布局控件。
// 
// 作  者：MPF开发组
// 时  间：2011-07-02
// 
// ============================================================================


#ifndef _UIWARPPANEL_H_
#define _UIWARPPANEL_H_

#include <Extend/suiwgxconfig.h>
#include <Framework/Controls/Panel.h>
#include <System/Windows/ScrollInfo.h>

namespace suic
{

class SUIWGX_API WrapPanel : public Panel
{
public:

    static DpProperty* ItemWidthProperty;
    static DpProperty* ItemHeightProperty;

    static DpProperty* OrientationProperty;

    static bool StaticInit();

    static void OnOrientationPropChanged(DpObject* d, DpPropChangedEventArg* e);

    WrapPanel();
    virtual ~WrapPanel();

    RTTIOfClass(WrapPanel)

    void SetItemWidth(Float val);
    void SetItemHeight(Float val);

    Float GetItemWidth();
    Float GetItemHeight();

    /// <summary>
    ///  获取界面元素的方向
    /// </summary>
    /// <remarks>
    ///  界面元素的方向分为水平和垂直（Horizontal和Vertical）。
    /// </remarks>
    /// <returns>Horizontal: 水平; Vertical: 垂直</returns> 
    Orientation GetOrientation();
    void SetOrientation(Orientation val);

protected:

    void EnsureScrollingData(fSize viewport, fSize extent, fPoint offset);

    void OnScrollChanged();

    fSize OnMeasure(const fSize& size);
    void OnArrange(const fSize& arrangeSize);

protected:

    ScrollData* GetScrollData();
    IScrollInfo* GetScrollInfo();
    void ArrangeLine(int v, int lineV, int start, int end, bool useItemU, int itemU);

protected:

    ScrollInfo _scrollInfo;
    int _firstVisible;
    int _visibleCount;
};

inline IScrollInfo* WrapPanel::GetScrollInfo()
{
    return &_scrollInfo;
}

inline void WrapPanel::SetItemWidth(Float val)
{
    SetValue(ItemWidthProperty, new OFloat(val));
}

inline void WrapPanel::SetItemHeight(Float val)
{
    SetValue(ItemHeightProperty, new OFloat(val));
}

inline Float WrapPanel::GetItemWidth()
{
    return GetValue(ItemWidthProperty)->ToFloat();
}

inline Float WrapPanel::GetItemHeight()
{
    return GetValue(ItemHeightProperty)->ToFloat();
}

inline Orientation WrapPanel::GetOrientation()
{
    return (Orientation)GetValue(OrientationProperty)->ToInt();
}

inline void WrapPanel::SetOrientation(Orientation val)
{
    SetValue(OrientationProperty, OrientationBox::From(val));
}

}

#endif
