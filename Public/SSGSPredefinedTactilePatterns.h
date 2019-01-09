#pragma once


#include "SSGSPredefinedTactilePatterns.generated.h"


USTRUCT( BlueprintType )
struct FPredefinedTactilePattern
{
    GENERATED_BODY();
    UPROPERTY( BlueprintReadOnly ) FString name;
};


#define SSGS_DECLARE_TACTILE_PATTERN(NAME) \
    UFUNCTION( BlueprintCallable, BlueprintPure, meta = ( NativeMakeFunc ) ) \
    static const FPredefinedTactilePattern pattern_ ## NAME () { \
        return FPredefinedTactilePattern{ FString( TEXT( "ti_predefined_" #NAME ) ) }; \
    }

UCLASS( BlueprintType )
class UPredefinedTactilePatternFactory : public UObject
{

    GENERATED_BODY()

public:

    SSGS_DECLARE_TACTILE_PATTERN( strongclick_100 );
    SSGS_DECLARE_TACTILE_PATTERN( strongclick_60 );
    SSGS_DECLARE_TACTILE_PATTERN( strongclick_30 );
    SSGS_DECLARE_TACTILE_PATTERN( sharpclick_100 );
    SSGS_DECLARE_TACTILE_PATTERN( sharpclick_60 );
    SSGS_DECLARE_TACTILE_PATTERN( sharpclick_30 );
    SSGS_DECLARE_TACTILE_PATTERN( softbump_100 );
    SSGS_DECLARE_TACTILE_PATTERN( softbump_60 );
    SSGS_DECLARE_TACTILE_PATTERN( softbump_30 );
    SSGS_DECLARE_TACTILE_PATTERN( doubleclick_100 );
    SSGS_DECLARE_TACTILE_PATTERN( doubleclick_60 );
    SSGS_DECLARE_TACTILE_PATTERN( tripleclick_100 );
    SSGS_DECLARE_TACTILE_PATTERN( softfuzz_60 );
    SSGS_DECLARE_TACTILE_PATTERN( strongbuzz_100 );
    SSGS_DECLARE_TACTILE_PATTERN( buzzalert750ms );
    SSGS_DECLARE_TACTILE_PATTERN( buzzalert1000ms );
    SSGS_DECLARE_TACTILE_PATTERN( strongclick1_100 );
    SSGS_DECLARE_TACTILE_PATTERN( strongclick2_80 );
    SSGS_DECLARE_TACTILE_PATTERN( strongclick3_60 );
    SSGS_DECLARE_TACTILE_PATTERN( strongclick4_30 );
    SSGS_DECLARE_TACTILE_PATTERN( mediumclick1_100 );
    SSGS_DECLARE_TACTILE_PATTERN( mediumclick2_80 );
    SSGS_DECLARE_TACTILE_PATTERN( mediumclick3_60 );
    SSGS_DECLARE_TACTILE_PATTERN( sharptick1_100 );
    SSGS_DECLARE_TACTILE_PATTERN( sharptick2_80 );
    SSGS_DECLARE_TACTILE_PATTERN( sharptick3_60 );
    SSGS_DECLARE_TACTILE_PATTERN( shortdoubleclickstrong1_100 );
    SSGS_DECLARE_TACTILE_PATTERN( shortdoubleclickstrong2_80 );
    SSGS_DECLARE_TACTILE_PATTERN( shortdoubleclickstrong3_60 );
    SSGS_DECLARE_TACTILE_PATTERN( shortdoubleclickstrong4_30 );
    SSGS_DECLARE_TACTILE_PATTERN( shortdoubleclickmedium1_100 );
    SSGS_DECLARE_TACTILE_PATTERN( shortdoubleclickmedium2_80 );
    SSGS_DECLARE_TACTILE_PATTERN( shortdoubleclickmedium3_60 );
    SSGS_DECLARE_TACTILE_PATTERN( shortdoublesharptick1_100 );
    SSGS_DECLARE_TACTILE_PATTERN( shortdoublesharptick2_80 );
    SSGS_DECLARE_TACTILE_PATTERN( shortdoublesharptick3_60 );
    SSGS_DECLARE_TACTILE_PATTERN( longdoublesharpclickstrong1_100 );
    SSGS_DECLARE_TACTILE_PATTERN( longdoublesharpclickstrong2_80 );
    SSGS_DECLARE_TACTILE_PATTERN( longdoublesharpclickstrong3_60 );
    SSGS_DECLARE_TACTILE_PATTERN( longdoublesharpclickstrong4_30 );
    SSGS_DECLARE_TACTILE_PATTERN( longdoublesharpclickmedium1_100 );
    SSGS_DECLARE_TACTILE_PATTERN( longdoublesharpclickmedium2_80 );
    SSGS_DECLARE_TACTILE_PATTERN( longdoublesharpclickmedium3_60 );
    SSGS_DECLARE_TACTILE_PATTERN( longdoublesharptick1_100 );
    SSGS_DECLARE_TACTILE_PATTERN( longdoublesharptick2_80 );
    SSGS_DECLARE_TACTILE_PATTERN( longdoublesharptick3_60 );
    SSGS_DECLARE_TACTILE_PATTERN( buzz1_100 );
    SSGS_DECLARE_TACTILE_PATTERN( buzz2_80 );
    SSGS_DECLARE_TACTILE_PATTERN( buzz3_60 );
    SSGS_DECLARE_TACTILE_PATTERN( buzz4_40 );
    SSGS_DECLARE_TACTILE_PATTERN( buzz5_20 );
    SSGS_DECLARE_TACTILE_PATTERN( pulsingstrong1_100 );
    SSGS_DECLARE_TACTILE_PATTERN( pulsingstrong2_60 );
    SSGS_DECLARE_TACTILE_PATTERN( pulsingmedium1_100 );
    SSGS_DECLARE_TACTILE_PATTERN( pulsingmedium2_60 );
    SSGS_DECLARE_TACTILE_PATTERN( pulsingsharp1_100 );
    SSGS_DECLARE_TACTILE_PATTERN( pulsingsharp2_60 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionclick1_100 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionclick2_80 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionclick3_60 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionclick4_40 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionclick5_20 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionclick6_10 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionhum1_100 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionhum2_80 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionhum3_60 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionhum4_40 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionhum5_20 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionhum6_10 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownlongsmooth1_100to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownlongsmooth2_100to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownmediumsmooth1_100to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownmediumsmooth2_100to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownshortsmooth1_100to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownshortsmooth2_100to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownlongsharp1_100to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownlongsharp2_100to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownmediumsharp1_100to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownmediumsharp2_100to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownshortsharp1_100to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownshortsharp2_100to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampuplongsmooth1_0to100 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampuplongsmooth2_0to100 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampupmediumsmooth1_0to100 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampupmediumsmooth2_0to100 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampupshortsmooth1_0to100 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampupshortsmooth2_0to100 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampuplongsharp1_0to100 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampuplongsharp2_0to100 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampupmediumsharp1_0to100 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampupmediumsharp2_0to100 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampupshortsharp1_0to100 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampupshortsharp2_0to100 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownlongsmooth1_50to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownlongsmooth2_50to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownmediumsmooth1_50to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownmediumsmooth2_50to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownshortsmooth1_50to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownshortsmooth2_50to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownlongsharp1_50to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownlongsharp2_50to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownmediumsharp1_50to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownmediumsharp2_50to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownshortsharp1_50to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampdownshortsharp2_50to0 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampuplongsmooth1_0to50 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampuplongsmooth2_0to50 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampupmediumsmooth1_0to50 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampupmediumsmooth2_0to50 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampupshortsmooth1_0to50 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampupshortsmooth2_0to50 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampuplongsharp1_0to50 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampuplongsharp2_0to50 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampupmediumsharp1_0to50 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampupmediumsharp2_0to50 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampupshortsharp1_0to50 );
    SSGS_DECLARE_TACTILE_PATTERN( transitionrampupshortsharp2_0to50 );
    SSGS_DECLARE_TACTILE_PATTERN( longbuzzforprogrammaticstopping_100 );
    SSGS_DECLARE_TACTILE_PATTERN( smoothhum1nokickorbrakepulse_50 );
    SSGS_DECLARE_TACTILE_PATTERN( smoothhum2nokickorbrakepulse_40 );
    SSGS_DECLARE_TACTILE_PATTERN( smoothhum3nokickorbrakepulse_30 );
    SSGS_DECLARE_TACTILE_PATTERN( smoothhum4nokickorbrakepulse_20 );
    SSGS_DECLARE_TACTILE_PATTERN( smoothhum5nokickorbrakepulse_10 );

};