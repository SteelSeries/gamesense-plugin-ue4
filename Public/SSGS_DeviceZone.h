#pragma once


#include "SSGS_DeviceZone.generated.h"


USTRUCT( BlueprintType )
struct FSSGS_IlluminationDeviceZone {

    GENERATED_BODY();

    FSSGS_IlluminationDeviceZone() {}
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

    UPROPERTY( BlueprintReadOnly ) FString device;
    UPROPERTY( BlueprintReadOnly ) FString zone;

};

UCLASS( BlueprintType )
class USSGS_IlluminationDeviceZoneFactory: public UObject {

    GENERATED_BODY()

public:

    // generic types

    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgb1zone_one() { return { "rgb-1-zone", "one" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgb2zone_one() { return{ "rgb-2-zone", "one" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgb2zone_two() { return{ "rgb-2-zone", "two" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgb3zone_one() { return{ "rgb-3-zone", "one" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgb3zone_two() { return{ "rgb-3-zone", "two" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgb3zone_three() { return{ "rgb-3-zone", "three" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgb4zone_one() { return{ "rgb-4-zone", "one" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgb4zone_two() { return{ "rgb-4-zone", "two" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgb4zone_three() { return{ "rgb-4-zone", "three" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgb4zone_four() { return{ "rgb-4-zone", "four" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgb5zone_one() { return{ "rgb-5-zone", "one" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgb5zone_two() { return{ "rgb-5-zone", "two" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgb5zone_three() { return{ "rgb-5-zone", "three" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgb5zone_four() { return{ "rgb-5-zone", "four" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgb5zone_five() { return{ "rgb-5-zone", "five" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_function_keys() { return{ "rgb-per-key-zones", "function-keys" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_number_keys() { return{ "rgb-per-key-zones", "number-keys" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_q_row() { return{ "rgb-per-key-zones", "q-row" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_a_row() { return{ "rgb-per-key-zones", "a-row" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_z_row() { return{ "rgb-per-key-zones", "z-row" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_macro_keys() { return{ "rgb-per-key-zones", "macro-keys" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_main_keyboard() { return{ "rgb-per-key-zones", "main-keyboard" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_nav_cluster() { return{ "rgb-per-key-zones", "nav-cluster" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_kwypad_nums() { return{ "rgb-per-key-zones", "keypad-nums" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_arrows() { return{ "rgb-per-key-zones", "arrows" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_keypad() { return{ "rgb-per-key-zones", "keypad" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_all() { return{ "rgb-per-key-zones", "all" }; }


    // concrete types

    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_mouse_logo() { return{ "mouse", "logo" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_mouse_wheel() { return{ "mouse", "wheel" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_keyboad_keypad() { return{ "keyboard", "keypad" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_keyboad_function_keys() { return{ "keyboard", "function-keys" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_keyboad_main_keyboard() { return{ "keyboard", "main-keyboard" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_keyboad_number_keys() { return{ "keyboard", "number-keys" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_keyboad_macro_keys() { return{ "keyboard", "macro-keys" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_headset_earcups() { return{ "headset", "earcups" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FSSGS_IlluminationDeviceZone make_indicator_one() { return{ "indicator", "one" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
    static const FSSGS_IlluminationDeviceZone make_rgbperkeyzones_custom( const TArray< uint8 >& v ) {
        return FSSGS_IlluminationDeviceZone{ TEXT( "rgb-per-key-zones" ), v };
    }
};

UCLASS( BlueprintType )
class USSGS_TactileDeviceZoneFactory: public UObject {

    GENERATED_BODY()

public:

    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
    static const FSSGS_TactileDeviceZone make_tactile_one() {
        return FSSGS_TactileDeviceZone{ "tactile", "one" };
    }

};
