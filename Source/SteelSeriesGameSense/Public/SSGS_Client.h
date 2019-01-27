#pragma once


#include "Types/SSGS_Payload.h"


namespace ssgs {


bool STEELSERIESGAMESENSE_API Start();
void STEELSERIESGAMESENSE_API Stop();
void STEELSERIESGAMESENSE_API RegisterGame( const FSSGS_GameInfo& v );
void STEELSERIESGAMESENSE_API RegisterEvent( const FSSGS_EventInfo& v );
void STEELSERIESGAMESENSE_API BindEvent( const FSSGS_EventBinding& v );
void STEELSERIESGAMESENSE_API SendEvent( const FSSGS_EventUpdate& v );
void STEELSERIESGAMESENSE_API RemoveEvent( const FSSGS_Event& v );
void STEELSERIESGAMESENSE_API RemoveGame( const FSSGS_Game& v );


};
