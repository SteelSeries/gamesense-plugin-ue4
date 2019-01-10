#pragma once


//#include "CoreMinimal.h"
#include "Containers/Union.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "Runtime/Json/Public/Json.h"
#include "Serialization/JsonSerializerMacros.h"
#include "Runtime/Core/Public/Async/Future.h"


#include "SSGS_DeviceZone.h"
#include "SSGS_PredefinedTactilePatterns.h"
#include "SSGS_JsonConvertable.h"

#include "Types/SSGS_Enums.h"
#include "Types/SSGS_Frequency.h"
#include "Types/SSGS_RepeatLimit.h"
#include "Types/SSGS_FrequencyRepeatLimitPair.h"
#include "Types/SSGS_RateStatic.h"
#include "Types/SSGS_RateRange.h"
#include "Types/SSGS_RateSpecification.h"
#include "Types/SSGS_RGB.h"
#include "Types/SSGS_Gradient.h"
#include "Types/SSGS_ColorGradient.h"
#include "Types/SSGS_ColorRangeStatic.h"
#include "Types/SSGS_ColorRangeGradient.h"
#include "Types/SSGS_ColorEffectSpecification.h"
#include "Types/SSGS_ColorEffectSpecificationStatic.h"
#include "Types/SSGS_ColorEffectSpecificationGradient.h"
#include "Types/SSGS_ColorEffectSpecificationRanges.h"
#include "Types/SSGS_TactileEffectSimple.h"
#include "Types/SSGS_TactileEffectCustom.h"
#include "Types/SSGS_TactilePatternSpecification.h"

#include "Types/SSGS_HandlerColor.h"
#include "Types/SSGS_HandlerTactile.h"

#include "Types/SSGS_HandlerCollection.h"
#include "Types/SSGS_EventData.h"

#include "SSGS_Payload.h"
#include "SSGSClient.h"
#include "SSGS_ClientBPLibrary.h"