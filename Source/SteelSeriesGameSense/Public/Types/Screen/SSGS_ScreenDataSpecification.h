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


#include "SSGS_FrameData.h"
#include "SSGS_ScreenDataSpecification.generated.h"


UCLASS( BlueprintType, Abstract, meta = ( Category = "Gamesense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_ScreenDataSpecification : public UObject, public FSSGS_JsonConvertable {

    GENERATED_BODY()

public:

    virtual ~USSGS_ScreenDataSpecification() {}
    virtual TSharedPtr< FJsonValue > Convert() const { return TSharedPtr< FJsonValue >( nullptr ); }

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification" )
    static FSSGS_FrameData MakeSingleLineFrameData( const FSSGS_LineData& lineData, FSSGS_FrameModifiers frameModifiers );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification" )
    static FSSGS_FrameData MakeMultiLineFrameData( const TArray< FSSGS_LineData >& lines, FSSGS_FrameModifiers frameModifiers );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification" )
    static FSSGS_FrameData MakeImageFrameData( UPARAM( ref )USSGS_ImageDataSource*& source, FSSGS_FrameModifiers frameModifiers );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification", meta = ( AutoCreateRefTerm = "accessor" ) )
    static FSSGS_LineData MakeTextLineData( const FSSGS_LineDataText& textModifiers, const FSSGS_LineDataAccessor& accessor );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification", meta = ( AutoCreateRefTerm = "accessor" ) )
    static FSSGS_LineData MakeProgressBarLineData( const FSSGS_LineDataAccessor& accessor );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification" )
    static FSSGS_FrameModifiers MakeFrameModifiers( int32 length_millis, ESSGS_EventIconId icon_id, bool repeats );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification" )
    static FSSGS_FrameModifiers MakeFrameModifiersWithRepeatCount( int32 length_millis, ESSGS_EventIconId icon_id, int32 repeat_count );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification" )
    static FSSGS_FrameModifiers MakeFrameModifiersWithNoRepeat( int32 length_millis, ESSGS_EventIconId icon_id );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification" )
    static FSSGS_LineDataAccessor MakeContextFrameKeyAccessor( const FString& key );

    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification" )
    static FSSGS_LineDataAccessor MakeGoLispExpressionAccessor( const FString& expression );

    static FSSGS_LineData MakeTextLineData( const FSSGS_LineDataText& textModifiers );
    static FSSGS_LineData MakeProgressBarLineData();

protected:

    USSGS_ScreenDataSpecification() {};

};
