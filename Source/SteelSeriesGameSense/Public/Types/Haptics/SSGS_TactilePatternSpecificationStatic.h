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


#include "SSGS_TactilePatternSpecification.h"
#include "SSGS_TactilePatternStatic.h"
#include "SSGS_TactilePatternSpecificationStatic.generated.h"


UCLASS( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_TactilePatternSpecificationStatic : public USSGS_TactilePatternSpecification {

    GENERATED_BODY()

public:

    /**
    * Properly constructs USSGS_TactilePatternSpecificationStatic object.
    *
    * @param    pattern Array of variant (predefined/custom) pattern objects.
    * @return   USSGS_TactilePatternSpecificationStatic object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|TactilePatternSpecification" )
    static USSGS_TactilePatternSpecificationStatic* MakeStaticTactilePattern( const TArray< FSSGS_TactilePatternStatic >& pattern );

    /**
    * Construct a predefined static pattern variant.
    *
    * @param    type Predefined tactile pattern. Use USSGS_PredefinedTactilePatternFactory to obtain correct value.
    * @param    delay_ms Delay amount in milliseconds.
    * @return   FSSGS_TactilePatternStatic object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|TactilePatternSpecification" ) )
    static FSSGS_TactilePatternStatic MakeStaticWithPredefinedEffect( const FSSGS_PredefinedTactilePattern& type, int32 delay_ms = 0 );

    /**
    * Construct a custom static pattern variant.
    *
    * @param    length_ms Duration of the effect in milliseconds.
    * @param    delay_ms Delay amount in milliseconds.
    * @return   FSSGS_TactilePatternStatic object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|TactilePatternSpecification" ) )
    static FSSGS_TactilePatternStatic MakeStaticWithCustomEffect( int32 length_ms, int32 delay_ms = 0 );

    /**
    * Construct an empty static pattern variant (for parts of ranges where you want no effect)
    *
    * @return USSGS_TactilePatternStatic object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc, Category = "Gamesense|TactilePatternSpecification") )
    static TArray<FSSGS_TactilePatternStatic> MakeStaticEmptyPattern( );

    TSharedPtr< FJsonValue > Convert() const;

private:

    TArray< FSSGS_TactilePatternStatic > _pattern;

};
