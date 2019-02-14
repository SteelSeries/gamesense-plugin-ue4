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
#include "Types/SSGS_Enums.h"
#include "Types/SSGS_EventData.h"
#include "Types/Handler/SSGS_HandlerCollection.h"
#include "SSGS_Payload.generated.h"


// ***** root payload structures *****
USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_GameInfo: public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_GameInfo();
    FSSGS_GameInfo( const FString& game, const FString& displayName );

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString game;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString gameDisplayName;

    TSharedPtr< FJsonValue > Convert() const;

};

USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_EventInfo: public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_EventInfo();
    FSSGS_EventInfo( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId );

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString game;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString eventName;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 minValue;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 maxValue;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) ESSGS_EventIconId iconId;

    TSharedPtr< FJsonValue > Convert() const;

};

USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_EventBinding : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_EventBinding();
    FSSGS_EventBinding( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId, USSGS_HandlerCollection* handlers );
    ~FSSGS_EventBinding();

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString game;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString eventName;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 minValue;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 maxValue;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) ESSGS_EventIconId iconId;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, meta=( DisplayName = "Handler Collection" ) )
    USSGS_HandlerCollection* handlers;

    TSharedPtr< FJsonValue > Convert() const;

};

USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_EventUpdate: public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_EventUpdate();
    FSSGS_EventUpdate( const FString& game, const FString& eventName, const FSSGS_EventData& data );

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString game;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString eventName;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FSSGS_EventData data;

    TSharedPtr< FJsonValue > Convert() const;

};

USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_Event: public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_Event();
    FSSGS_Event( const FString& game, const FString& eventName );

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString game;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString eventName;

    TSharedPtr< FJsonValue > Convert() const;

};

USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_Game: public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_Game();
    FSSGS_Game( const FString& game );

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString game;

    TSharedPtr< FJsonValue > Convert() const;

};
