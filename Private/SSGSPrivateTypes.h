#pragma once


#include "SSGSPrivateTypes.generated.h"


template <typename T>
FString _getEnumString( const FString& name, T value )
{
    static const UEnum* pEnum;
    if ( !pEnum ) {
        pEnum = FindObject< UEnum >( ( UObject* )ANY_PACKAGE, *name, true );
        if ( !pEnum ) {
            return FString( TEXT( "Enum class \"" ) ) + name + FString( TEXT( "\" not found" ) );
        }
    }

    return pEnum->GetDisplayNameTextByValue( ( int64 )value ).ToString();
}

#define GetEnumString(TYPE,VALUE) _getEnumString( #TYPE, VALUE )

USTRUCT()
struct F_server_props_ {
    GENERATED_BODY();

    UPROPERTY()
    FString address;
};

template <typename T>
T* _createUObj()
{
    T* p = NewObject< T >();
    p->AddToRoot();
    return p;
}