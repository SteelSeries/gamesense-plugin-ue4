#pragma once


#include "SSGS_Enums.generated.h"


UENUM( BlueprintType )
enum class ESSGS_IconColor : uint8 {
    Orange = 0,
    Gold = 1,
    Yellow = 2,
    Green = 3,
    Teal = 4,
    LightBlue = 5,
    Blue = 6,
    Purple = 7,
    Fuschia = 8,
    Pink = 9,
    Red = 10,
    Silver = 11
};

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
    TactilePatternStatic_Predefined,
    TactilePatternStatic_Custom
};

enum ESSGS_TactilePatternType {
    TactilePatternType_Simple = 0,
    TactilePatternType_Custom
    // TODO TactilePatternType_Range
};

enum ESSGS_RangeColorEffect {
    RangeColorEffect_Static = 0,
    RangeColorEffect_Gradient
};

UENUM( BlueprintType )
enum class ESSGS_IlluminationMode : uint8 {
    Color = 0 UMETA( DisplayName = "color" ),
    Percent UMETA( DisplayName = "percent" ),
    Count UMETA( DisplayName = "count" )
};
