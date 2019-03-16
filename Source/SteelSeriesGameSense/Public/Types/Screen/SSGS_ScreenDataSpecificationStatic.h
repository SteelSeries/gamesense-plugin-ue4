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


#include "SSGS_ScreenDataSpecification.h"
#include "SSGS_FrameData.h"
#include "SSGS_ScreenDataSpecificationStatic.generated.h"


UCLASS( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_ScreenDataSpecificationStatic : public USSGS_ScreenDataSpecification {

    GENERATED_BODY()

public:

    /**
    * Properly construct static frame data.
    *
    * @param    datas Array of objects describing each frame.
    * @return   USSGS_ScreenDataSpecificationStatic object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification" )
    static USSGS_ScreenDataSpecificationStatic* MakeStaticScreenData( const TArray< FSSGS_FrameData >& datas );

    TSharedPtr< FJsonValue > Convert() const;

    UPROPERTY() TArray< FSSGS_FrameData > datas;

};
