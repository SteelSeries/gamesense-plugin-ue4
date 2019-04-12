/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
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
    Item = 17,
    AtSymbol = 18,
    Muted = 19,
    Talking = 20,
    Connect = 21,
    Disconnect = 22,
    Music = 23,
    Play = 24,
    Pause = 25
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
