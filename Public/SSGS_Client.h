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

};
