// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SoundRecogniser.generated.h"

/**
 * 
 */
UCLASS()
class AUDIOVISUAL_API USoundRecogniser : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/**
	*Spits out the number of currently active sounds
	*
	*@outparam	Value - The number of sounds currently active
	*
	*
	*
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext), Category = "HUD|Util")
	static float ActiveSoundNumber();

};
