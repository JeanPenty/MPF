// 华勤科技版权所有 2010-2011
// 
// 文件名：VisualizeStackPanel.h
// 功  能：虚拟列表。
// 
// 作  者：MPF开发组
// 时  间：2011-07-02
// 
// ============================================================================


#ifndef _UIVISUALIZINGSTACKPANEL_H_
#define _UIVISUALIZINGSTACKPANEL_H_

#include <System/Windows/ScrollInfo.h>
#include <Framework/Controls/VisualizePanel.h>

namespace suic
{

class ItemsControl;

class SUICORE_API IProvideStackingSize
{
public:

    virtual ~IProvideStackingSize() {}
    virtual fSize EstimatedContainerSize(bool isHorizontal) = 0;
    virtual Float GetHeaderSize(bool isHorizontal) = 0;
};

/// <summary>
/// VirtualizingStackPanel
/// </summary>
class SUICORE_API VirtualizingStackPanel : public VirtualizingPanel
{
public:

    static DpProperty* OrientationProperty;

    static bool StaticInit();
    static void OnOrientationPropChanged(DpObject* d, DpPropChangedEventArg* e);

    RTTIOfClass(VirtualizingStackPanel)

    VirtualizingStackPanel();
    virtual ~VirtualizingStackPanel();

    IScrollInfo* GetScrollInfo();
    ScrollData* GetScrollData();
    bool IsScrolling();

    /// <summary>
    ///  获取界面元素的方向
    /// </summary>
    /// <remarks>
    ///  界面元素的方向分为水平和垂直（Horizontal和Vertical）。
    /// </remarks>
    /// <returns>Horizontal: 水平; Vertical: 垂直</returns> 
    Orientation GetOrientation();
    void SetOrientation(Orientation val);

    int GetLogicalOrientation();

    void ClearAllContainers(ItemsControl* itemsControl);

    int GetVisibleStart() const;

public:

    int GetVisibleChildrenCount();
    void InvalidateChildrenResourceReference();

    fSize OnMeasure(const fSize& constraintSize);
    void OnArrange(const fSize& arrangesize);
    
protected:

    virtual void OnScrollChange();
    virtual void OnViewportSizeChanged(fSize oldViewportSize, fSize newViewportSize);
    virtual void OnViewportOffsetChanged(fPoint oldViewportOffset, fPoint newViewportOffset);
    virtual void OnItemsChangedInternal(Object* sender, ItemsChangedEventArg* e);

    fSize MeasureCommon(const fSize& constraint);

    void HandleMoreContainer();
    void ClearRealizedContainer();
    void InsertContainer(int index, Element* conainer);
    Element* RecycleContainer(int index, ItemEntry* item);

    void SetAndVerifyScrollingData(fSize viewport, fSize prevSize, fSize extent, fPoint offset);
    void AdjustViewportOffset(MeasureData& measureData, ItemsControl* itemsControl, bool isHori);

    void ResetChildMeasureData(MeasureData* childMeasureData, const MeasureData& measureData, fSize layoutSize, fSize stackSize, bool bHori);
    int CalcFirstVisibleItemOffset(ItemsControl* itemsOwner, MeasureData& measureData, bool bHori, Float& firstItemOffset, fSize& stackOffset);

protected:

    int _realedCount;
    int _visibleCount;
    int _visibleStart;
    Float _visibleOffset;
    Float _visibleMeasure;

    ScrollInfo* _scrollInfo;
};

inline int VirtualizingStackPanel::GetVisibleChildrenCount()
{
    return _visibleCount;
}

inline int VirtualizingStackPanel::GetVisibleStart() const
{
    return _visibleStart;
}

inline Orientation VirtualizingStackPanel::GetOrientation()
{
    return (Orientation)GetValue(OrientationProperty)->ToInt();
}

inline int VirtualizingStackPanel::GetLogicalOrientation()
{
    return GetOrientation();
}

inline void VirtualizingStackPanel::SetOrientation(Orientation val)
{
    SetValue(OrientationProperty, OrientationBox::From(val));
}

}

#endif
