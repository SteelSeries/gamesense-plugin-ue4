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


#include "SSGS_LineData.h"
#include "SSGS_FrameModifiers.h"
#include "SSGS_FrameDataMultiLine.generated.h"


USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_FrameDataMultiLine : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_FrameDataMultiLine() {}
    FSSGS_FrameDataMultiLine( const TArray< FSSGS_LineData >& lines, const FSSGS_FrameModifiers& frameModifiers, ESSGS_EventIconId icon_id = ESSGS_EventIconId::Default ) :
        lines( lines ), frameModifiers( frameModifiers ), icon_id( icon_id ) {}

    TSharedPtr< FJsonValue > Convert() const;

    UPROPERTY() TArray< FSSGS_LineData > lines;
    UPROPERTY() FSSGS_FrameModifiers frameModifiers;
    UPROPERTY() ESSGS_EventIconId icon_id;

};
