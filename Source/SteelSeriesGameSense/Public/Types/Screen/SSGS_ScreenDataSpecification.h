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

    /**
    * Construct frame data for a single line.
    *
    * @param    lineData Object describing the line contents.
    * @param    frameModifiers Object for frame customization.
    * @param    icon_id Optional id of icon to display alongside the text.
    * @return   FSSGS_FrameData object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification" )
    static FSSGS_FrameData MakeSingleLineFrameData( const FSSGS_LineData& lineData, FSSGS_FrameModifiers frameModifiers, ESSGS_EventIconId icon_id = ESSGS_EventIconId::Default );

    /**
    * Construct frame data for multiple lines.
    *
    * @param    lines Array of objects describing each line contents.
    * @param    frameModifiers Object for frame customization.
    * @param    icon_id Optional id of icon to display alongside the text.
    * @return   FSSGS_FrameData object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification" )
    static FSSGS_FrameData MakeMultiLineFrameData( const TArray< FSSGS_LineData >& lines, FSSGS_FrameModifiers frameModifiers, ESSGS_EventIconId icon_id = ESSGS_EventIconId::Default );

    /**
    * Construct frame data from raw image.
    *
    * @param    source Object supplying raw image data.
    * @param    dz Device - Zone object for source validation.
    * @param    frameModifiers Object for frame customization.
    * @return   FSSGS_FrameData object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification" )
    static FSSGS_FrameData MakeImageFrameData( UPARAM( ref )USSGS_ImageDataSource*& source, const FSSGS_ScreenDeviceZone& dz, FSSGS_FrameModifiers frameModifiers );

    /**
    * Construct line data out of text.
    *
    * @param    textModifiers Customizes how text is presented.
    * @param    accessor Specifies the source of text data.
    * @return   FSSGS_LineData object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification", meta = ( AutoCreateRefTerm = "accessor" ) )
    static FSSGS_LineData MakeTextLineData( const FSSGS_LineDataText& textModifiers, const FSSGS_LineDataAccessor& accessor );
    static FSSGS_LineData MakeTextLineData( const FSSGS_LineDataText& textModifiers );

    /**
    * Construct line data to show a progress bar.
    *
    * @param    accessor Specifies the source value for the progress bar.
    * @return   FSSGS_LineData object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification", meta = ( AutoCreateRefTerm = "accessor" ) )
    static FSSGS_LineData MakeProgressBarLineData( const FSSGS_LineDataAccessor& accessor );
    static FSSGS_LineData MakeProgressBarLineData();

    /**
    * Construct frame modifiers
    *
    * @param    length_millis Specifies frame duration in milliseconds (0 = infinite).
    * @param    repeats Whether to repeat the frame sequence or not. Meaningful on the last frame.
    * @return   FSSGS_FrameModifiers object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification" )
    static FSSGS_FrameModifiers MakeFrameModifiers( int32 length_millis, bool repeats );

    /**
    * Construct frame modifiers
    *
    * @param    length_millis Specifies frame duration in milliseconds (0 = infinite).
    * @param    repeat_count Specifies the number of times the frame sequence is displayed (0 = infinite).
    * @return   FSSGS_FrameModifiers object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification" )
    static FSSGS_FrameModifiers MakeFrameModifiersWithRepeatCount( int32 length_millis, int32 repeat_count );

    /**
    * Construct frame modifiers for frames to be displayed only once.
    *
    * @param    length_millis Specifies frame duration in milliseconds (0 = infinite).
    * @return   FSSGS_FrameModifiers object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification" )
    static FSSGS_FrameModifiers MakeFrameModifiersWithNoRepeat( int32 length_millis );

    /**
    * Construct line data accessor with a key name.
    *
    * @param    key Key name to use to retrieve a value in the frame context.
    * @return   FSSGS_LineDataAccessor object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification" )
    static FSSGS_LineDataAccessor MakeContextFrameKeyAccessor( const FString& key );

    /**
    * Construct line data accessor with a GoLisp expression.
    *
    * @param    expression Golisp expression to obtain and optionally transform data.
    * @return   FSSGS_LineDataAccessor object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|ScreenDataSpecification" )
    static FSSGS_LineDataAccessor MakeGoLispExpressionAccessor( const FString& expression );

protected:

    USSGS_ScreenDataSpecification() {};

};
