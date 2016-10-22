// 华勤科技版权所有 2010-2011
// 
// 文件名：ColumnDefinition.h
// 功  能：实现列逻辑。
// 
// 作  者：MPF开发组
// 时  间：2011-07-02
// 
// ============================================================================


#ifndef _UICOLUMNDEFINITION_H_
#define _UICOLUMNDEFINITION_H_

#include <Framework/Controls/DefinitionBase.h>

namespace suic
{

class SUICORE_API ColumnDefinition : public DefinitionBase
{
public:

    static DpProperty* MaxWidthProperty;
    static DpProperty* MinWidthProperty;
    static DpProperty* WidthProperty;

    static bool StaticInit();

    static void OnWidthPropChanged(DpObject* d, DpPropChangedEventArg* e);

    RTTIOfClass(ColumnDefinition)

    ColumnDefinition();
    ~ColumnDefinition();

    GridSize* GetWidth();
    Float GetMinWidth();
    Float GetMaxWidth();

    void SetWidth(GridSize* val);
    void SetMinWidth(Float val);
    void SetMaxWidth(Float val);

    Float GetUserMinSize();
    Float GetUserMaxSize();

    GridSize* GetUserSize();
};

inline Float ColumnDefinition::GetUserMinSize()
{
    return GetMinWidth();
}

inline Float ColumnDefinition::GetUserMaxSize()
{
    return GetMaxWidth();
}

inline GridSize* ColumnDefinition::GetUserSize()
{
    return GetWidth();
}

inline GridSize* ColumnDefinition::GetWidth()
{
    return RTTIEqualCast<GridSize>(GetValue(WidthProperty));
}

inline Float ColumnDefinition::GetMinWidth()
{
    return GetValue(MinWidthProperty)->ToFloat();
}

inline Float ColumnDefinition::GetMaxWidth()
{
    return GetValue(MaxWidthProperty)->ToFloat();
}

inline void ColumnDefinition::SetWidth(GridSize* val)
{
    if (NULL != val)
    {
        SetValue(WidthProperty, val);
    }
}

inline void ColumnDefinition::SetMinWidth(Float val)
{
    SetValue(MinWidthProperty, new OFloat(val));
}

inline void ColumnDefinition::SetMaxWidth(Float val)
{
    SetValue(MaxWidthProperty, new OFloat(val));
}

class SUICORE_API ColumnDefinitions : public GridDefinitions
{
public:

    ColumnDefinitions();
    ~ColumnDefinitions();

    ColumnDefinition* GetColumnDef(int index)
    {
        return (ColumnDefinition*)(GetItem(index));
    }
};

};

#endif
