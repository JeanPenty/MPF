// 华勤科技版权所有 2010-2011
// 
// 文件名：RowDefinition.h
// 功  能：行逻辑。
// 
// 作  者：MPF开发组
// 时  间：2011-07-02
// 
// ============================================================================


#ifndef _UIROWDEFINITION_H_
#define _UIROWDEFINITION_H_

#include <Framework/Controls/DefinitionBase.h>

namespace suic
{

class SUICORE_API RowDefinition : public DefinitionBase
{
public:

    static DpProperty* MaxHeightProperty;
    static DpProperty* MinHeightProperty;
    static DpProperty* HeightProperty;

    static bool StaticInit();

    static void OnHeightPropChanged(DpObject* d, DpPropChangedEventArg* e);

    RTTIOfClass(RowDefinition)

    RowDefinition();
    ~RowDefinition();

    GridSize* GetHeight();
    Float GetMinHeight();
    Float GetMaxHeight();
    void SetHeight(GridSize* val);
    void SetMinHeight(Float val);
    void SetMaxHeight(Float val);

    Float GetUserMinSize();
    Float GetUserMaxSize();

    GridSize* GetUserSize();
};

inline Float RowDefinition::GetUserMinSize()
{
    return GetMinHeight();
}

inline Float RowDefinition::GetUserMaxSize()
{
    return GetMaxHeight();
}

inline GridSize* RowDefinition::GetUserSize()
{
    return GetHeight();
}

inline GridSize* RowDefinition::GetHeight()
{
    return RTTICast<GridSize>(GetValue(HeightProperty));
}

inline Float RowDefinition::GetMinHeight()
{
    return GetValue(MinHeightProperty)->ToFloat();
}

inline Float RowDefinition::GetMaxHeight()
{
    return GetValue(MaxHeightProperty)->ToFloat();
}

inline void RowDefinition::SetHeight(GridSize* val)
{
    if (val)
    {
        SetValue(HeightProperty, val);
    }
}

inline void RowDefinition::SetMinHeight(Float val)
{
    SetValue(MinHeightProperty, new OFloat(val));
}

inline void RowDefinition::SetMaxHeight(Float val)
{
    SetValue(MaxHeightProperty, new OFloat(val));
}

class SUICORE_API RowDefinitions : public GridDefinitions
{
public:

    RowDefinitions();
    ~RowDefinitions();

    RowDefinition* GetRowDef(int index)
    {
        return (RowDefinition*)(GetItem(index));
    }
};

};

#endif
