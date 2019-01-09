#pragma once


#include "Types/SSGS_Enums.h"
#include "SSGS_Payload.generated.h"


#define SSGS_CATEGORY "GameSense"


// ***** root payload structures *****
USTRUCT( BlueprintType )
struct STEELSERIESGAMESENSE_API FSSGS_GameInfo: public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_GameInfo();
    FSSGS_GameInfo( const FString& game, const FString& displayName, SSGS_IconColor iconColorId );

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString game;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString gameDisplayName;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) SSGS_IconColor iconColorId;

    TSharedPtr< FJsonValue > Convert() const;

};

USTRUCT( BlueprintType )
struct STEELSERIESGAMESENSE_API FSSGS_EventInfo: public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_EventInfo();
    FSSGS_EventInfo( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, SSGS_EventIconId iconId );

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString game;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString eventName;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 minValue;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 maxValue;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) SSGS_EventIconId iconId;

    TSharedPtr< FJsonValue > Convert() const;

};

USTRUCT( BlueprintType )
struct STEELSERIESGAMESENSE_API FSSGS_EventBinding : public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_EventBinding();
    FSSGS_EventBinding( const FString& gameName, const FString& eventName, int32 minValue, int32 maxValue, SSGS_EventIconId iconId, USSGS_HandlerCollection* handlers );

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString game;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString eventName;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 minValue;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) int32 maxValue;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) SSGS_EventIconId iconId;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) USSGS_HandlerCollection* handlers;

    TSharedPtr< FJsonValue > Convert() const;

};

USTRUCT( BlueprintType )
struct STEELSERIESGAMESENSE_API FSSGS_EventUpdate: public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_EventUpdate();
    FSSGS_EventUpdate( const FString& game, const FString& eventName, const FSSGS_EventData& data );

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString game;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString eventName;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FSSGS_EventData data;

    TSharedPtr< FJsonValue > Convert() const;

};

USTRUCT( BlueprintType )
struct STEELSERIESGAMESENSE_API FSSGS_Event: public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_Event();
    FSSGS_Event( const FString& game, const FString& eventName );

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString game;
    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString eventName;

    TSharedPtr< FJsonValue > Convert() const;

};

USTRUCT( BlueprintType )
struct STEELSERIESGAMESENSE_API FSSGS_Game: public FSSGS_JsonConvertable {

    GENERATED_BODY()

    FSSGS_Game();
    FSSGS_Game( const FString& game );

    UPROPERTY( EditAnywhere, BlueprintReadWrite ) FString game;

    TSharedPtr< FJsonValue > Convert() const;

};
