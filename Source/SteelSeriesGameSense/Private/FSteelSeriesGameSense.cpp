// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SSGS_Client.h"
#include "SSGS_ClientBPLibrary.h"
#include "ISteelSeriesGameSense.h"


class FSteelSeriesGameSense : public ISteelSeriesGameSense
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

IMPLEMENT_MODULE( FSteelSeriesGameSense, SteelSeriesGameSense )



void FSteelSeriesGameSense::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
}


void FSteelSeriesGameSense::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}



