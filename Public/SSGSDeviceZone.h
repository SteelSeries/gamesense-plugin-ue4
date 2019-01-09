#pragma once


#include "SSGSDeviceZone.generated.h"


USTRUCT( BlueprintType )
struct FIlluminationDeviceZone {

    GENERATED_BODY();

    FIlluminationDeviceZone() {}
    FIlluminationDeviceZone( const FString& device, const FString& zone ) : zoneType( named ), device( device ), _namedZone( zone ) {}

    FIlluminationDeviceZone( const FString& device, const TArray< uint8 >& zone ) : zoneType( custom ), device( device ), _customZone( zone ) {}

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
struct FTactileDeviceZone {

    GENERATED_BODY();
    UPROPERTY( BlueprintReadOnly ) FString device;
    UPROPERTY( BlueprintReadOnly ) FString zone;

};


#define _DEFINE_ILL_DEVICEZONE_FN_(NAME,DEVICE,ZONE) \
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) ) \
    static const FIlluminationDeviceZone make_ ## NAME () { \
        UE_LOG(LogTemp, Display, TEXT(#ZONE)); \
        return FIlluminationDeviceZone{ TEXT( #DEVICE ), TEXT( #ZONE ) }; \
    }

#define DEFINE_ILL_DEVICEZONE_FN(DEVICE,ZONENAME) _DEFINE_ILL_DEVICEZONE_FN_(DEVICE ## _ ## ZONENAME, DEVICE, ZONENAME)
#define DEFINE_ILL_DEVICEZONE_FN2(DEVICE,ZONENAME1,ZONENAME2) _DEFINE_ILL_DEVICEZONE_FN_(DEVICE ## _ ## ZONENAME1 ## _ ## ZONENAME2, DEVICE, ZONENAME1 ## - ## ZONENAME2)
#define DEFINE_ILL_GENERIC_DEVICEZONE_FN(NUMZONES,ZONE) _DEFINE_ILL_DEVICEZONE_FN_(rgb ## NUMZONES ## zone_ ## ZONE, rgb- ## NUMZONES ## -zone, ZONE)
#define DEFINE_ILL_RGBPERKEY_DEVICEZONE_FN(ZONENAME) _DEFINE_ILL_DEVICEZONE_FN_(rgbperkeyzones_ ## ZONENAME, rgb-per-key-zones, ZONENAME)
#define DEFINE_ILL_RGBPERKEY_DEVICEZONE_FN2(ZONENAME1, ZONENAME2) _DEFINE_ILL_DEVICEZONE_FN_(rgbperkeyzones_ ## ZONENAME1 ## _ ## ZONENAME2, rgb-per-key-zones, ZONENAME1 ## - ## ZONENAME2)


UCLASS( BlueprintType )
class UIlluminationDeviceZoneFactory: public UObject {

    GENERATED_BODY()

public:

    // generic types

    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgb1zone_one() { return { "rgb-1-zone", "one" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgb2zone_one() { return{ "rgb-2-zone", "one" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgb2zone_two() { return{ "rgb-2-zone", "two" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgb3zone_one() { return{ "rgb-3-zone", "one" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgb3zone_two() { return{ "rgb-3-zone", "two" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgb3zone_three() { return{ "rgb-3-zone", "three" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgb4zone_one() { return{ "rgb-4-zone", "one" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgb4zone_two() { return{ "rgb-4-zone", "two" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgb4zone_three() { return{ "rgb-4-zone", "three" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgb4zone_four() { return{ "rgb-4-zone", "four" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgb5zone_one() { return{ "rgb-5-zone", "one" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgb5zone_two() { return{ "rgb-5-zone", "two" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgb5zone_three() { return{ "rgb-5-zone", "three" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgb5zone_four() { return{ "rgb-5-zone", "four" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgb5zone_five() { return{ "rgb-5-zone", "five" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgbperkeyzones_function_keys() { return{ "rgb-per-key-zones", "function-keys" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgbperkeyzones_number_keys() { return{ "rgb-per-key-zones", "number-keys" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgbperkeyzones_q_row() { return{ "rgb-per-key-zones", "q-row" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgbperkeyzones_a_row() { return{ "rgb-per-key-zones", "a-row" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgbperkeyzones_z_row() { return{ "rgb-per-key-zones", "z-row" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgbperkeyzones_macro_keys() { return{ "rgb-per-key-zones", "macro-keys" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgbperkeyzones_main_keyboard() { return{ "rgb-per-key-zones", "main-keyboard" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgbperkeyzones_nav_cluster() { return{ "rgb-per-key-zones", "nav-cluster" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgbperkeyzones_kwypad_nums() { return{ "rgb-per-key-zones", "keypad-nums" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgbperkeyzones_arrows() { return{ "rgb-per-key-zones", "arrows" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgbperkeyzones_keypad() { return{ "rgb-per-key-zones", "keypad" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_rgbperkeyzones_all() { return{ "rgb-per-key-zones", "all" }; }


    // concrete types

    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_mouse_logo() { return{ "mouse", "logo" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_mouse_wheel() { return{ "mouse", "wheel" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_keyboad_keypad() { return{ "keyboard", "keypad" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_keyboad_function_keys() { return{ "keyboard", "function-keys" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_keyboad_main_keyboard() { return{ "keyboard", "main-keyboard" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_keyboad_number_keys() { return{ "keyboard", "number-keys" }; }
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_keyboad_macro_keys() { return{ "keyboard", "macro-keys" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_headset_earcups() { return{ "headset", "earcups" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
        static const FIlluminationDeviceZone make_indicator_one() { return{ "indicator", "one" }; }


    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) )
    static const FIlluminationDeviceZone make_rgbperkeyzones_custom( const TArray< uint8 >& v ) {
        return FIlluminationDeviceZone{ TEXT( "rgb-per-key-zones" ), v };
    }
};


#define DEFINE_TAC_DEVICEZONE_FN(DEVICE,ZONE) UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) ) \
    static const FTactileDeviceZone make_ ## DEVICE ## _ ## ZONE () { \
        return FTactileDeviceZone{ TEXT( #DEVICE ), TEXT( #ZONE ) }; \
    }

UCLASS( BlueprintType )
class UTactileDeviceZoneFactory: public UObject {

    GENERATED_BODY()

public:

    DEFINE_TAC_DEVICEZONE_FN( tactile, one );

};