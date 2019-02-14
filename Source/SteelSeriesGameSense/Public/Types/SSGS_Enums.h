/**
* authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once


#include "SSGS_Enums.generated.h"

UENUM( BlueprintType )
enum class ESSGS_EventIconId : uint8 {
    Default = 0,
    Health = 1,
    Armor = 2,
    Ammo = 3,
    Money = 4,
    Flashbang = 5,
    Kills = 6,
    Headshot = 7,
    Helmet = 8,
    Hunger = 10,
    Air = 11,
    Compass = 12,
    Tool = 13,
    Mana = 14,
    Clock = 15,
    Lightning = 16,
    Item = 17
};

UENUM( BlueprintType )
enum class ESSGS_ColorEffect : uint8 {
    Static = 0,
    Gradient,
    Ranges
};

enum ESSGS_HandlerType {
    HandlerType_Color = 0,
    HandlerType_Tactile
};

enum ESSGS_RateMode {
    RateMode_None = 0,
    RateMode_Static,
    RateMode_Range
};

enum ESSGS_TactilePatternStaticType {
    TactilePatternStatic_Invalid,
    TactilePatternStatic_Predefined,
    TactilePatternStatic_Custom
};

enum ESSGS_TactilePatternType {
    TactilePatternType_Simple = 0,
    TactilePatternType_Custom
    // TODO TactilePatternType_Range
};

enum ESSGS_RangeColorEffect {
    RangeColorEffect_Invalid = 0,
    RangeColorEffect_Static,
    RangeColorEffect_Gradient
};

UENUM( BlueprintType )
enum class ESSGS_IlluminationMode : uint8 {
    Color = 0 UMETA( DisplayName = "color" ),
    Percent UMETA( DisplayName = "percent" ),
    Count UMETA( DisplayName = "count" )
};
