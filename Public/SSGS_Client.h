#pragma once


#include "SteelSeriesGameSensePCH.h"


namespace ssgs {


bool Start();
void Stop();
void RegisterGame( const FSSGS_GameInfo& v );
void RegisterEvent( const FSSGS_EventInfo& v );
void BindEvent( const FSSGS_EventBinding& v );
void SendEvent( const FSSGS_EventUpdate& v );
void RemoveEvent( const FSSGS_Event& v );
void RemoveGame( const FSSGS_Game& v );


// convenience functions

USSGS_RateSpecification* MakeRateSpecification();
USSGS_HandlerCollection* MakeHandlerCollection();
USSGS_ColorEffectSpecificationStatic* MakeColorEffectSpecificationStatic();
USSGS_ColorEffectSpecificationGradient* MakeColorEffectSpecificationGradient();
USSGS_ColorEffectSpecificationRanges* MakeColorEffectSpecificationRanges();
USSGS_TactilePatternSpecificationStatic* MakeTactilePatternSpecificationStatic();


};
