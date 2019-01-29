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


#include "SSGS_ColorEffectSpecification.h"
#include "SSGS_ColorRange.h"
#include "SSGS_ColorEffectSpecificationRanges.generated.h"


UCLASS( BlueprintType, meta = ( Category = "GameSense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_ColorEffectSpecificationRanges : public USSGS_ColorEffectSpecification {

    GENERATED_BODY()

public:

    /**
    * Properly constructs USSGS_ColorEffectSpecificationRanges object.
    *
    * @param    v Array of color range variants.
    * @return   USSGS_ColorEffectSpecificationRanges object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "GameSense|ColorEffectSpecification" )
    static USSGS_ColorEffectSpecificationRanges* MakeRangeColorEffect( const TArray< FSSGS_ColorRange >& v );

    /**
    * Constructs a color range with a static color.
    *
    * @param    low Low end (inclusive) of the range.
    * @param    high High end (inclusive) of the range.
    * @param    color RGB color specification for the range.
    * @return   FSSGS_ColorRange object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "GameSense|ColorEffectSpecification" )
    static FSSGS_ColorRange MakeStaticColorRange( int32 low, int32 high, const FSSGS_RGB& color );

    /**
    * Constructs a color range with a gradient variant.
    *
    * @param    low Low end (inclusive) of the range.
    * @param    high High end (inclusive) of the range.
    * @param    zero Start color for the gradient.
    * @param    hundred End color for the gradient.
    * @return   FSSGS_ColorRange object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "GameSense|ColorEffectSpecification" )
    static FSSGS_ColorRange MakeGradientColorRange( int32 low, int32 high, UPARAM( DisplayName = "Start Color" ) const FSSGS_RGB& zero, UPARAM( DisplayName = "End Color" ) const FSSGS_RGB& hundred );

    TSharedPtr< FJsonValue > Convert() const;

    UPROPERTY() TArray< FSSGS_ColorRange > ranges;

};