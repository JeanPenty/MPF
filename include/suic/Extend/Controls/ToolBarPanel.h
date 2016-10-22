// 华勤科技版权所有 2010-2011
// 
// 文件名：ToolBarPanel.h
// 功  能：工具条面板
// 
// 作  者：MPF开发组
// 时  间：2010-08-31
// 
// =============================================================

#ifndef _UITOOLBARPANEL_H_
#define _UITOOLBARPANEL_H_

#include <Extend/suiwgxconfig.h>
#include <Framework/Controls/StackPanel.h>

namespace suic
{

class ToolBar;
class ToolBarPanel;

class SUIWGX_API ToolBarOverflowPanel : public Panel
{
public:

    static DpProperty* WrapWidthProperty;

    static bool StaticInit();

    static bool IsWrapWidthValid(Object* value);

    ToolBarOverflowPanel();

    int GetWrapWidth();
    void SetWrapWidth(int val);

private:

    void OnArrange(const fSize& arrangeBounds);
    fSize OnMeasure(const fSize& constraint);

    ElementColl* CreateUIElementCollection(FrameworkElement* logicalParent);

    void ArrangeLine(int y, int lineHeight, int start, int end);

    ToolBar* GetToolBar();
    ToolBarPanel* GetToolBarPanel();

private:
    
    fSize _panelSize;
    Float _wrapWidth;
};

/// <summary>
/// ToolBarPanel。
/// </summary>
class SUIWGX_API ToolBarPanel : public StackPanel
{
public:

    static bool StaticInit();

    static void OnOrientationPropChanged(DpObject* d, DpPropChangedEventArg* e);

    ToolBarPanel();
    virtual ~ToolBarPanel();

    RTTIOfClass(ToolBarPanel)

    int GetMinLength() const;
    void SetMinLength(int val);

    int GetMaxLength() const;
    void SetMaxLength(int val);

protected:

    IScrollInfo* GetScrollInfo();
    bool IsScrolling();

    Array<Element*>& GetGeneratedItemsCollection();

    friend class ToolBarOverflowPanel;

protected:

    void OnPreApplyTemplate();

    fSize OnMeasure(const fSize& constraintSize);
    void OnArrange(const fSize& arrangesize);

    void OnItemsChangedInternal(Object* sender, ItemsChangedEventArg* e);

private:

    ToolBar* GetToolBar();
    ToolBarOverflowPanel* GetToolBarOverflowPanel();
    bool MeasureGeneratedItems(bool asNeededPass, fSize constraint, bool horizontal, 
        Float maxExtent, fSize& panelDesiredSize, Float& overflowExtent);

    void GenerateChildren();
    void RemoveAt(Element* child);
    void AddChildren(int pos, int itemCount);
    void MoveChildren(int fromPos, int toPos, int containerCount);
    void RemoveChildren(int pos, int containerCount);
    void ReplaceChildren(int pos, int itemCount, int containerCount);

private:

    int _minLength;
    int _maxLength;
    Array<Element*> _generatedItemsCollection;

};

}

#endif
