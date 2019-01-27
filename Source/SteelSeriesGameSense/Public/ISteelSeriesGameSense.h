// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"

#define STEELSERIESGAMESENSE_SUPPORTED_PLATFORMS (PLATFORM_MAC || (PLATFORM_WINDOWS && WINVER >= 0x0601))


/**
 * The public interface to this module
 */
class ISteelSeriesGameSense : public IModuleInterface
{

public:

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline ISteelSeriesGameSense& Get()
	{
		return FModuleManager::LoadModuleChecked< ISteelSeriesGameSense >( "ISteelSeriesGameSense" );
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded( "ISteelSeriesGameSense" );
	}
};

