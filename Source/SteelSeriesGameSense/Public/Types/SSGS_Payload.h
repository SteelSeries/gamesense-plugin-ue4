/**
* Authors: sharkgoesmad
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once


#include "Common/SSGS_JsonConvertable.h"
#include "Types/SSGS_Enums.h"
#include "Types/EventData/SSGS_EventData.h"
#include "Types/Handler/SSGS_HandlerCollection.h"
#include "SSGS_Payload.generated.h"


// ***** root payload structures *****
USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_GameInfo: public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_GameInfo();
    FSSGS_GameInfo( const FString& game, const FString& displayName );
    FSSGS_GameInfo( const FString& game, const FString& displayName, const FString& developer );

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" )
    FString game;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Metadata" )
    FString gameDisplayName;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Metadata" )
    FString developer;

    TSharedPtr< FJsonValue > Convert() const;

};

USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_EventInfo: public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_EventInfo();
    FSSGS_EventInfo( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId, bool valueOptional = false );

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" )
    FString game;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" )
    FString eventName;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Metadata" )
    int32 minValue;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Metadata" )
    int32 maxValue;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Metadata" )
    ESSGS_EventIconId iconId;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Metadata" )
    bool valueOptional;

    TSharedPtr< FJsonValue > Convert() const;

};

USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_EventBinding : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_EventBinding();
    FSSGS_EventBinding( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, ESSGS_EventIconId iconId, USSGS_HandlerCollection* handlers, bool valueOptional = false );
    ~FSSGS_EventBinding();

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" )
    FString game;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" )
    FString eventName;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Metadata" )
    int32 minValue;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Metadata" )
    int32 maxValue;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Metadata" )
    ESSGS_EventIconId iconId;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Metadata" )
    bool valueOptional;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, meta=( DisplayName = "Handler Collection" ), Category="Mandatory" )
    USSGS_HandlerCollection* handlers;

    TSharedPtr< FJsonValue > Convert() const;

};

USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_EventUpdate: public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_EventUpdate();
    FSSGS_EventUpdate( const FString& game, const FString& eventName, const FSSGS_EventData& data );

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" ) FString game;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" ) FString eventName;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" ) FSSGS_EventData data;

    TSharedPtr< FJsonValue > Convert() const;

};

USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_Event: public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_Event();
    FSSGS_Event( const FString& game, const FString& eventName );

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" ) FString game;
    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" ) FString eventName;

    TSharedPtr< FJsonValue > Convert() const;

};

USTRUCT( BlueprintType, meta = ( Category = "Gamesense|Types" ) )
struct STEELSERIESGAMESENSE_API FSSGS_Game: public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_Game();
    FSSGS_Game( const FString& game );

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Mandatory" ) FString game;

    TSharedPtr< FJsonValue > Convert() const;

};
