// 华勤科技版权所有 2010-2011
// 
// 文件名：Embbed.h
// 功  能：富文本嵌入对象接口定义。
// 
// 作  者：MPF开发组
// 时  间：2010-07-02
// 
// ============================================================================

#ifndef _UIEMBBED_H_
#define _UIEMBBED_H_

#include <Extend/suiwgxconfig.h>

#include <System/Windows/Element.h>
#include <System/Graphics/Bitmap.h>

namespace suic
{

class RichTextBox;

class SUIWGX_API Embbed : public suic::Object
{
public:

    RTTIOfAbstractClass(Embbed)

    Embbed();
    virtual ~Embbed();

    void Invalidate(bool bForce);

    Object* GetHolder() const;
    void SetHolder(suic::Object* holder);

    suic::fSize GetDesiredSize();

    suic::fPoint GetVisualOffet() const;
    suic::fSize GetRenderSize() const;

    void Arrange(const suic::fRect& arrangeRect);
    void Measure(const suic::fSize& contraint);

    void Render(suic::Drawing* drawing);

    void Save(suic::ISStream* strm);
    void Restore(int type, suic::ISStream* strm);

    virtual int GetType();

protected:

    virtual void OnArrange(const suic::fRect& arrangeRect);
    virtual void OnMeasure(const suic::fSize& contraint);

    virtual void OnRender(suic::Drawing* drawing);
    virtual void OnSave(suic::ISStream* strm);
    virtual void OnRestore(int type, suic::ISStream* strm);

protected:

    // 嵌入对象大小
    suic::fSize _desiredSize;
    suic::fSize _renderSize;
    suic::fPoint _offset;

private:

    suic::WeakRef _holder;

    friend class RichTextBox;
};

}

#endif
