/**
* Authors: Joel Hunsley
*
* Copyright (c) 2019 SteelSeries ApS. All Rights Reserved.
*/
#pragma once

#include "Common/SSGS_JsonConvertable.h"
#include "Types/SSGS_Enums.h"
#include "Types/SSGS_Payload.h"
#include "SSGS_MultiEventUpdate.generated.h"

// The MultiEventUpdate struct is not used directly by the client, so it's not exposed as a blueprint type

USTRUCT()
struct STEELSERIESGAMESENSE_API FSSGS_MultiEventUpdate: public FSSGS_JsonConvertable {

    GENERATED_BODY()

    ~FSSGS_MultiEventUpdate();

    FSSGS_MultiEventUpdate();
    FSSGS_MultiEventUpdate( const FString& game );

    void AddEventUpdate(const FSSGS_EventUpdate& event);

    TSharedPtr< FJsonValue > Convert() const;

    UPROPERTY( EditAnywhere, Category="Mandatory" ) FString game;
    UPROPERTY()                                     TArray< FSSGS_EventUpdate > _events;
};