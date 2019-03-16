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


#include "Engine/Texture2D.h"
#include "Types/SSGS_DeviceZone.h"
#include "SSGS_FrameModifiers.h"
#include "SSGS_FrameDataImage.generated.h"


UCLASS( BlueprintType, Abstract, meta = ( Category = "Gamesense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_ImageDataSource : public UObject {

    GENERATED_BODY()

public:

    virtual ~USSGS_ImageDataSource() {}
    virtual TArray< uint8 > GetData() { return TArray< uint8 >();  }

protected:

    USSGS_ImageDataSource() {}

};

UCLASS( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_ImageDataTexture2D final : public USSGS_ImageDataSource {

    GENERATED_BODY()

public:

    TArray< uint8 > GetData() final;

    /**
    * Properly construct image data source from texture resource. The luma component will
    * be computed and thresholded for each color.
    *
    * @param    dz Device-zone object that supplies screen dimensions.
    * @param    texture Texture resource.
    * @return   USSGS_ImageDataTexture2D object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|Screen|ImageData" )
    static USSGS_ImageDataTexture2D* MakeImageDataFromTexture( const FSSGS_ScreenDeviceZone& dz, UTexture2D* texture );

private:

    FSSGS_ScreenDeviceZone _dz;
    UTexture2D* _pTex;

};

UCLASS( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_ImageDataArray final : public USSGS_ImageDataSource {

    GENERATED_BODY()

public:

    static USSGS_ImageDataArray* MakeImageDataFromArray( TArray< uint8 >&& packedBinaryImage );

    /**
    * Properly construct image data source from the supplied bit vector whose bit length
    * must match the screen area (width * height).
    *
    * @param    packedBinaryImage Bit vector.
    * @return   USSGS_ImageDataArray object.
    */
    UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Gamesense|Screen|ImageData" )
    static USSGS_ImageDataArray* MakeImageDataFromArray( const TArray< uint8 >& packedBinaryImage );

    TArray< uint8 > GetData() final;

private:

    TArray< uint8 > _arr;

};

USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_FrameDataImage : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_FrameDataImage() {}
    FSSGS_FrameDataImage( USSGS_ImageDataSource* pSrc, const FSSGS_FrameModifiers& frameModifiers );

    TSharedPtr< FJsonValue > Convert() const;

    UPROPERTY() TArray< uint8 > imageData;
    UPROPERTY() FSSGS_FrameModifiers frameModifiers;

};
