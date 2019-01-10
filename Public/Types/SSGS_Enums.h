#pragma once


#include "SSGS_Enums.generated.h"


UENUM( BlueprintType )
enum class SSGS_IconColor : uint8 {
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
enum class SSGS_EventIconId : uint8 {
    Default = 0,    // Blank display, no icon
    Health = 1,     // Health
    Armor = 2,      // Armor
    Ammo = 3,       // Ammo/Ammunition
    Money = 4,      // Money
    Flashbang = 5,  // Flash/Flashbang/Explosion
    Kills = 6,      // Kills
    Headshot = 7,   // Headshot
    Helmet = 8,     // Helmet
    Hunger = 10,    // Hunger
    Air = 11,       // Air/Breath
    Compass = 12,   // Compass
    Tool = 13,      // Tool/Pickaxe
    Mana = 14,      // Mana/Potion
    Clock = 15,     // Clock
    Lightning = 16, // Lightning
    Item = 17       // Item/Backpack
};

UENUM( BlueprintType )
enum class SSGS_ColorEffect : uint8 {
    Static = 0,
    Gradient,
    Ranges
};

enum SSGS_HandlerType {
    HandlerType_Color = 0,
    HandlerType_Tactile
};

enum SSGS_RateMode {
    RateMode_None = 0,
    RateMode_Static,
    RateMode_Range
};

enum SSGS_TactilePatternType {
    TactilePatternType_Simple = 0,
    TactilePatternType_Custom
    // TODO TactilePatternType_Range
};

enum SSGS_RangeColorEffect {
    RangeColorEffect_Static = 0,
    RangeColorEffect_Gradient
};

UENUM( BlueprintType )
enum class SSGS_IlluminationMode : uint8 {
    Color = 0 UMETA( DisplayName = "color" ),
    Percent UMETA( DisplayName = "percent" ),
    Count UMETA( DisplayName = "count" )
};
