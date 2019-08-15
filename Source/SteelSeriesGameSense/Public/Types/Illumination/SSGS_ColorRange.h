/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "Common/SSGS_JsonConvertable.h"
#include "Common/SSGS_Union.h"
#include "Types/SSGS_Enums.h"
#include "SSGS_ColorRangeStatic.h"
#include "SSGS_ColorRangeGradient.h"
#include "SSGS_ColorRange.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_ColorRange : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_ColorRange() : _type( RangeColorEffect_Invalid ) {};
    FSSGS_ColorRange( const FSSGS_ColorRangeStatic& v );
    FSSGS_ColorRange( const FSSGS_ColorRangeGradient& v );

    TSharedPtr< FJsonValue > Convert() const;
    
private:

    ESSGS_RangeColorEffect _type;
    ssgs::Union< FSSGS_ColorRangeStatic, FSSGS_ColorRangeGradient > _color;

};