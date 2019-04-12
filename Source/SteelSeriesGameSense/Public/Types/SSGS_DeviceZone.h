/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "SSGS_DeviceZone.generated.h"


// TODO hide make & break in blueprints
USTRUCT( BlueprintType )
struct FSSGS_IlluminationDeviceZone {

    GENERATED_BODY();

    FSSGS_IlluminationDeviceZone() : zoneType( named ), device( TEXT( "*** BAD VALUE ***" ) ), _namedZone( TEXT( "*** BAD VALUE ***" ) ) {}
    FSSGS_IlluminationDeviceZone( const FString& device, const FString& zone ) : zoneType( named ), device( device ), _namedZone( zone ) {}

    FSSGS_IlluminationDeviceZone( const FString& device, const TArray< uint8 >& zone ) : zoneType( custom ), device( device ), _customZone( zone ) {}

    enum {
        named = 0,
        custom
    } zoneType;
    FString device;

    const FString& namedZone() const { return _namedZone; }
    const TArray< uint8 >& customZone() const { return _customZone; }

private:

    FString _namedZone;
    TArray< uint8 > _customZone;

};

USTRUCT( BlueprintType )
struct FSSGS_TactileDeviceZone {

    GENERATED_BODY();

    FSSGS_TactileDeviceZone() : device( TEXT( "*** BAD VALUE ***" ) ), zone( TEXT( "*** BAD VALUE ***" ) ) {}
    FSSGS_TactileDeviceZone( const FString& device, const FString& zone ) : device( device ), zone( zone ) {}

    FString device;
    FString zone;

};

UCLASS()
class USSGS_IlluminationDeviceZoneFactory: public UObject {

    GENERATED_BODY()

public:

    // generic types

    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Zoned Device", DisplayName = "RGB-1-Zone One" ) )
    static const FSSGS_IlluminationDeviceZone make_rgb1zone_one() { return { "rgb-1-zone", "one" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Zoned Device", DisplayName = "RGB-2-Zone One" ) )
    static const FSSGS_IlluminationDeviceZone make_rgb2zone_one() { return { "rgb-2-zone", "one" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Zoned Device", DisplayName = "RGB-2-Zone Two" ) )
    static const FSSGS_IlluminationDeviceZone make_rgb2zone_two() { return { "rgb-2-zone", "two" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Zoned Device", DisplayName = "RGB-3-Zone One" ) )
    static const FSSGS_IlluminationDeviceZone make_rgb3zone_one() { return { "rgb-3-zone", "one" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Zoned Device", DisplayName = "RGB-3-Zone Two" ) )
    static const FSSGS_IlluminationDeviceZone make_rgb3zone_two() { return { "rgb-3-zone", "two" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Zoned Device", DisplayName = "RGB-3-Zone Three" ) )
    static const FSSGS_IlluminationDeviceZone make_rgb3zone_three() { return { "rgb-3-zone", "three" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Zoned Device", DisplayName = "RGB-4-Zone One" ) )
    static const FSSGS_IlluminationDeviceZone make_rgb4zone_one() { return { "rgb-4-zone", "one" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Zoned Device", DisplayName = "RGB-4-Zone Two" ) )
    static const FSSGS_IlluminationDeviceZone make_rgb4zone_two() { return { "rgb-4-zone", "two" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Zoned Device", DisplayName = "RGB-4-Zone Three" ) )
    static const FSSGS_IlluminationDeviceZone make_rgb4zone_three() { return { "rgb-4-zone", "three" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Zoned Device", DisplayName = "RGB-4-Zone Four" ) )
    static const FSSGS_IlluminationDeviceZone make_rgb4zone_four() { return { "rgb-4-zone", "four" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Zoned Device", DisplayName = "RGB-5-Zone One" ) )
    static const FSSGS_IlluminationDeviceZone make_rgb5zone_one() { return { "rgb-5-zone", "one" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Zoned Device", DisplayName = "RGB-5-Zone Two" ) )
    static const FSSGS_IlluminationDeviceZone make_rgb5zone_two() { return { "rgb-5-zone", "two" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Zoned Device", DisplayName = "RGB-5-Zone Three" ) )
    static const FSSGS_IlluminationDeviceZone make_rgb5zone_three() { return { "rgb-5-zone", "three" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Zoned Device", DisplayName = "RGB-5-Zone Four" ) )
    static const FSSGS_IlluminationDeviceZone make_rgb5zone_four() { return { "rgb-5-zone", "four" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Zoned Device", DisplayName = "RGB-5-Zone Five" ) )
    static const FSSGS_IlluminationDeviceZone make_rgb5zone_five() { return { "rgb-5-zone", "five" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Per Key Keyboard", DisplayName = "RGB-Per-Key-Zones Function Keys" ) )
    static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_function_keys() { return { "rgb-per-key-zones", "function-keys" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Per Key Keyboard", DisplayName = "RGB-Per-Key-Zones Number Keys" ) )
    static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_number_keys() { return { "rgb-per-key-zones", "number-keys" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Per Key Keyboard", DisplayName = "RGB-Per-Key-Zones Q Row" ) )
    static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_q_row() { return { "rgb-per-key-zones", "q-row" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Per Key Keyboard", DisplayName = "RGB-Per-Key-Zones A Row" ) )
    static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_a_row() { return { "rgb-per-key-zones", "a-row" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Per Key Keyboard", DisplayName = "RGB-Per-Key-Zones Z Row" ) )
    static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_z_row() { return { "rgb-per-key-zones", "z-row" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Per Key Keyboard", DisplayName = "RGB-Per-Key-Zones Macro Keys" ) )
    static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_macro_keys() { return { "rgb-per-key-zones", "macro-keys" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Per Key Keyboard", DisplayName = "RGB-Per-Key-Zones Main Keyboard" ) )
    static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_main_keyboard() { return { "rgb-per-key-zones", "main-keyboard" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Per Key Keyboard", DisplayName = "RGB-Per-Key-Zones Nav Cluster" ) )
    static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_nav_cluster() { return { "rgb-per-key-zones", "nav-cluster" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Per Key Keyboard", DisplayName = "RGB-Per-Key-Zones Keypad Numbers" ) )
    static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_keypad_nums() { return { "rgb-per-key-zones", "keypad-nums" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Per Key Keyboard", DisplayName = "RGB-Per-Key-Zones Arrows" ) )
    static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_arrows() { return { "rgb-per-key-zones", "arrows" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Per Key Keyboard", DisplayName = "RGB-Per-Key-Zones Keypad" ) )
    static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_keypad() { return { "rgb-per-key-zones", "keypad" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Per Key Keyboard", DisplayName = "RGB-Per-Key-Zones All" ) )
    static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_all() { return { "rgb-per-key-zones", "all" }; }


    // concrete types

    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|General Device Types", DisplayName = "Mouse Logo" ) )
    static const FSSGS_IlluminationDeviceZone make_mouse_logo() { return { "mouse", "logo" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|General Device Types", DisplayName = "Mouse Wheel" ) )
    static const FSSGS_IlluminationDeviceZone make_mouse_wheel() { return { "mouse", "wheel" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|General Device Types", DisplayName = "Keyboard Keypad" ) )
    static const FSSGS_IlluminationDeviceZone make_keyboad_keypad() { return { "keyboard", "keypad" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|General Device Types", DisplayName = "Keyboard Function Keys" ) )
    static const FSSGS_IlluminationDeviceZone make_keyboad_function_keys() { return { "keyboard", "function-keys" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|General Device Types", DisplayName = "Keyboard Main Keyboard" ) )
    static const FSSGS_IlluminationDeviceZone make_keyboad_main_keyboard() { return { "keyboard", "main-keyboard" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|General Device Types", DisplayName = "Keyboard Number Keys" ) )
    static const FSSGS_IlluminationDeviceZone make_keyboad_number_keys() { return { "keyboard", "number-keys" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|General Device Types", DisplayName = "Keyboard Macro Keys" ) )
    static const FSSGS_IlluminationDeviceZone make_keyboad_macro_keys() { return { "keyboard", "macro-keys" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|General Device Types", DisplayName = "Headset Earcups" ) )
    static const FSSGS_IlluminationDeviceZone make_headset_earcups() { return { "headset", "earcups" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|General Device Types", DisplayName = "Indicator One" ) )
    static const FSSGS_IlluminationDeviceZone make_indicator_one() { return { "indicator", "one" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|RGB Per Key Keyboard", DisplayName = "RGB-Per-Key-Zones Custom Zone" ) )
    static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_custom( const TArray< uint8 >& v ) {
        return FSSGS_IlluminationDeviceZone{ TEXT( "rgb-per-key-zones" ), v };
    }
};

UCLASS()
class USSGS_TactileDeviceZoneFactory: public UObject {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|Device Zones|Tactile" ) )
    static const FSSGS_TactileDeviceZone make_tactile_one() {
        return FSSGS_TactileDeviceZone{ "tactile", "one" };
    }

};
