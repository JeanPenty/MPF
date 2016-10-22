// 华勤科技版权所有 2010-2011
// 
// 文件名：SystemParameters.h
// 功  能：定义系统常量。
// 
// 作  者：MPF开发组
// 时  间：2010-07-02
// 
// ============================================================================

#ifndef _UISYSTEMPARAMETERS_H_
#define _UISYSTEMPARAMETERS_H_

#include <System/Types/StringCore.h>

namespace suic
{

struct SUICORE_API SystemParameters
{
    static int MessageFontSize;
    static String MessageFontName;

    static Float DpiX;
    static Float DpiY;

    static Float DpiScaleX;
    static Float DpiScaleY;

    static float RoundDpiValue(float val, float dpiScale);

    static fSize TransformToDevice(fSize size);
    static fSize TransformFromDevice(fSize size);

    static fRect TransformToDevice(fRect rect);
    static fRect TransformFromDevice(fRect rect);
};

}

#endif
