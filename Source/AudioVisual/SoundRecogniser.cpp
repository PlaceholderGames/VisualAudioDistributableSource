// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundRecogniser.h"
#include "AudioVisual.h"
#include "EngineUtils.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "ActiveSound.h"
#include "Sound/SoundWave.h"
#include "UObject/Class.h"
#include "AssetData.h"
#include "AudioDevice.h"
#include "AudioDeviceManager.h"
#include "IAudioExtensionPlugin.h"



template<typename T>
void GetObjectsOfClass(TArray<T*>& OutArray)
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData;
	AssetRegistryModule.Get().GetAssetsByClass(T::StaticClass()->GetFName(), AssetData);
	for (int i = 0; i < AssetData.Num(); i++) {
		T* Object = Cast<T>(AssetData[i].GetAsset());
		OutArray.Add(Object);
	}
}


float USoundRecogniser::ActiveSoundNumber()
{
	float value = 0.0;

	FAudioDevice* audioDevice = GEngine->GetActiveAudioDevice().GetAudioDevice();

	const TArray<FActiveSound*> activeSounds = audioDevice->GetActiveSounds();
	//FActiveSound* soundPtr = activeSounds&.GetData();

	for (int i = 0; i < activeSounds.Num(); i++)
	{
		FActiveSound* soundPtr = activeSounds[i];
		if (soundPtr->bIsPlayingAudio)
			value = value + 1.0;
	}
	/*
	for (auto& i : activeSounds)
	{
		value = value + 1;

	}
	*/

	return value;
}

FVector USoundRecogniser::ActiveSoundDistanceVector(const FVector& DistanceTo)
{
	FVector DistanceOut;

	FAudioDevice* audioDevice = GEngine->GetActiveAudioDevice().GetAudioDevice();

	const TArray<FActiveSound*> activeSounds = audioDevice->GetActiveSounds();
	//FActiveSound* soundPtr = activeSounds&.GetData();

	/*
	need to check if sound is hearable by player / audio device / listener before determining distance
	checking volume in listener?
	*/

	for (int i = 0; i < activeSounds.Num(); i++)
	{
		FActiveSound* soundPtr = activeSounds[i];
		if (soundPtr->bIsPlayingAudio)
		{
			DistanceOut = soundPtr->LastLocation;
			
		}
	}
	/*
	for (auto& i : activeSounds)
	{
		value = value + 1;

	}
	*/
	DistanceOut = DistanceOut - DistanceTo;

	return DistanceOut;
}