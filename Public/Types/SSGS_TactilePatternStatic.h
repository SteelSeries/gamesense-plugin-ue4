#pragma once


#include "SSGS_TactilePatternStatic.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "GameSense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_TactilePatternStatic : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_TactilePatternStatic() : _type( TactilePatternStatic_Invalid ), _pattern() {}
    FSSGS_TactilePatternStatic( const FSSGS_TactileEffectPredefined& v );
    FSSGS_TactilePatternStatic( const FSSGS_TactileEffectCustom& v );
    FSSGS_TactilePatternStatic( const FSSGS_TactilePatternStatic& other );
    FSSGS_TactilePatternStatic& operator=( const FSSGS_TactilePatternStatic& rhs );

    TSharedPtr< FJsonValue > Convert() const;

private:

    ESSGS_TactilePatternStaticType _type;
    union __pattern {
#pragma warning(disable:4582)
        __pattern() {}
#pragma warning(default:4582)
#pragma warning(disable:4583)
        ~__pattern() {}
#pragma warning(default:4583)

        uint8 _invalid = 0;
        FSSGS_TactileEffectPredefined predefined;
        FSSGS_TactileEffectCustom custom;
    } _pattern;

};
