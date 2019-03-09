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
#include "Types/Screen/SSGS_ScreenDataSpecification.h"
#include "SSGS_HandlerScreen.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_HandlerScreen : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_HandlerScreen();
    FSSGS_HandlerScreen( const FSSGS_HandlerScreen& other );
    FSSGS_HandlerScreen( const FSSGS_ScreenDeviceZone& deviceZone, USSGS_ScreenDataSpecification* dataSpec );
    const FSSGS_HandlerScreen& operator=( const FSSGS_HandlerScreen& other );
    ~FSSGS_HandlerScreen();

    TSharedPtr< FJsonValue > Convert() const;

    UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = ( DisplayName = "Device - Zone" ) )
    FSSGS_ScreenDeviceZone deviceZone;
    UPROPERTY( EditAnywhere, BlueprintReadWrite )
    FString mode = TEXT( "screen" );
    UPROPERTY( EditAnywhere, BlueprintReadWrite, meta = ( DisplayName = "Screen Data Specification" ) )
    USSGS_ScreenDataSpecification* data;

};