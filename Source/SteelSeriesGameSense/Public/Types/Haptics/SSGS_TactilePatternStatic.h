/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "Common/SSGS_JsonConvertable.h"
#include "Common/SSGS_Union.h"
#include "Types/SSGS_Enums.h"
#include "SSGS_TactileEffectPredefined.h"
#include "SSGS_TactileEffectCustom.h"
#include "SSGS_TactilePatternStatic.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_TactilePatternStatic : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_TactilePatternStatic() : _type( TactilePatternStatic_Invalid ) {}
    FSSGS_TactilePatternStatic( const FSSGS_TactileEffectPredefined& v );
    FSSGS_TactilePatternStatic( const FSSGS_TactileEffectCustom& v );

    TSharedPtr< FJsonValue > Convert() const;

private:

    ESSGS_TactilePatternStaticType _type;
    ssgs::Union< FSSGS_TactileEffectPredefined, FSSGS_TactileEffectCustom > _pattern;

};
