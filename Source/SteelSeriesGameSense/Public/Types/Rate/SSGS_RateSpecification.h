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


#include "Common/SSGS_JsonConvertable.h"
#include "Common/SSGS_Union.h"
#include "Types/SSGS_Enums.h"
#include "SSGS_FrequencyRepeatLimitPair.h"
#include "SSGS_RateStatic.h"
#include "SSGS_RateRange.h"
#include "SSGS_RateSpecification.generated.h"


UCLASS( BlueprintType, meta = ( Category = "GameSense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_RateSpecification : public UObject, public FSSGS_JsonConvertable {

    GENERATED_BODY()

public:

    /**
    * Properly constructs USSGS_RateSpecification with static variant.
    *
    * @param    frequency Specifies the frequency component of the rate object in Hz.
    * @param    repeat_limit Repeat count for the rate object.
    * @return   USSGS_ColorEffectSpecificationRanges object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "GameSense|RateSpecification" )
    static USSGS_RateSpecification* MakeStaticRate( int32 frequency, int32 repeat_limit );

    /**
    * Properly constructs USSGS_RateSpecification with ranges variant.
    *
    * @param    v Array of ranges.
    * @return   USSGS_ColorEffectSpecificationRanges object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "GameSense|RateSpecification" )
    static USSGS_RateSpecification* MakeRangedRate( UPARAM( DisplayName = "Frequency - RepeatLimit Pairs" ) const TArray< FSSGS_FrequencyRepeatLimitPair >& v );

    TSharedPtr< FJsonValue > Convert() const;

private:

    ESSGS_RateMode _mode;
    ssgs::Union< FSSGS_RateStatic, FSSGS_RateRange > _rate;

};