// 华勤科技版权所有 2010-2011
// 
// 文件名：Border.h
// 功  能：定义核心库边框类，封装元素的边框和背景绘制逻辑。
// 
// 作  者：MPF开发组
// 时  间：2010-05-02
// 
// ============================================================================

#ifndef _UIBORDER_H_
#define _UIBORDER_H_

#include <Framework/Controls/Decorator.h>

namespace suic
{

/// <summary>
/// 边框控件
/// </summary>
class SUICORE_API Border : public Decorator
{
public:

    static DpProperty* CornerRadiusProperty;
    static DpProperty* BackgroundProperty;
    static DpProperty* PaddingProperty;
    static DpProperty* BorderBrushProperty;
    static DpProperty* BorderThicknessProperty;

    static bool StaticInit();

    static void OnBackgroundPropChanged(DpObject* d, DpPropChangedEventArg* e);
    static void OnForegroundPropChanged(DpObject* d, DpPropChangedEventArg* e);
    static void OnPaddingPropChanged(DpObject* d, DpPropChangedEventArg* e);
    static void OnBorderBrushPropChanged(DpObject* d, DpPropChangedEventArg* e);
    static void OnBorderThicknessPropChanged(DpObject* d, DpPropChangedEventArg* e);

    Border();
    virtual ~Border();

    RTTIOfClass(Border)

    fRect GetCornerRadius();
    void SetCornerRadius(fRect val);

    fRect GetPadding();
    void SetPadding(fRect val);

    Brush* GetBackground();
    void SetBackground(Brush* val);

    Brush* GetBorderBrush();
    void SetBorderBrush(Brush* val);

    fRect GetBorderThickness();
    void SetBorderThickness(fRect border);

protected:

    void ResetCachedBitmap();
    void UpdateCachedBitmap(Drawing* drawing);

    void RenderChildren(Drawing* drawing);
    bool EnterRenderChildren(Drawing* drawing);
    void ExitRenderChildren(Drawing* drawing);

    bool HitTestCore(HitTestCtx* hitResult, bool onlySelf);

    fSize OnMeasure(const fSize& availableSize);
    void OnArrange(const fSize& arrangeSize);

    void OnRenderSizeChanged(SizeChangedInfo& e);

    void OnRender(Drawing * drawing);

protected:

    fRect _thickness;
    fRect _padding;
    
    Brush* _background;
    Brush* _foreground;
    Brush* _borderBrush;

    Bitmap* _cachedBitmap;
};

}

#endif
