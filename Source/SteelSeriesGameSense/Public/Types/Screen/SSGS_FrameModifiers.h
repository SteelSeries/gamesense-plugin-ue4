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


#include "Common/SSGS_Union.h"
#include "Types/SSGS_Enums.h"
#include "SSGS_FrameModifiers.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_FrameModifiers : public FSSGS_JsonConvertable {
    
    GENERATED_BODY()

    FSSGS_FrameModifiers() : FSSGS_FrameModifiers( 0 ) {}
    FSSGS_FrameModifiers( int32 length_millis, bool repeats ) :
        length_millis( length_millis ), _repeats_type( Boolean ), _repeats( repeats ) {}
    FSSGS_FrameModifiers( int32 length_millis, int32 repeat_count ) :
        length_millis( length_millis ), _repeats_type( Integer ), _repeats( repeat_count ) {}
    FSSGS_FrameModifiers( int32 length_millis ) :
        length_millis( length_millis ), _repeats_type( None ) {}

    void Decorate( TSharedPtr<FJsonObject> obj ) const;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Optional" ) int32 length_millis;

private:

    enum _type_ {
        Boolean = 0,
        Integer,
        None
    };

private:

    _type_ _repeats_type;
    ssgs::Union< int32, bool > _repeats;

};
