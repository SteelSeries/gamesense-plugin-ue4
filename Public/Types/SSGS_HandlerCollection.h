#pragma once


#include "SSGS_HandlerColor.h"
#include "SSGS_HandlerTactile.h"
#include "SSGS_HandlerCollection.generated.h"


UCLASS( BlueprintType, meta = ( Category = "GameSense|Types" ) )
class STEELSERIESGAMESENSE_API USSGS_HandlerCollection : public UObject, public FSSGS_JsonConvertable {

    GENERATED_BODY()

public:

    USSGS_HandlerCollection();
    ~USSGS_HandlerCollection();

    UFUNCTION( BlueprintCallable, Category = "GameSense|HandlerCollection" )
    void AddColorHandler( const FSSGS_HandlerColor& handler );

    UFUNCTION( BlueprintCallable, Category = "GameSense|HandlerCollection" )
    void AddTactileHandler( const FSSGS_HandlerTactile& handler );

    TSharedPtr< FJsonValue > Convert() const;

private:

    TArray< FSSGS_HandlerColor > _colorHandlers;
    TArray< FSSGS_HandlerTactile > _tactileHandlers;

};