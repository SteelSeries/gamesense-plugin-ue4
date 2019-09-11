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


#include "Types/EventData/SSGS_FrameObject.h"
#include "SSGS_EventData.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_EventData : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_EventData() : value( 0 ), frame( nullptr ) {}
    FSSGS_EventData( int32 value ) : value( value ), frame( nullptr ) {}
    FSSGS_EventData( int32 value, USSGS_Frame* frame ) : value( value ), frame( frame ) {}

    TSharedPtr< FJsonValue > Convert() const;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Data" ) int32 value;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Data" ) USSGS_Frame* frame;

};
