// Fill out your copyright notice in the Description page of Project Settings.

#include "AudioVisual.h"
#include "SoundRecogniser.h"
#include "EngineUtils.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "ActiveSound.h"
#include "Sound/SoundWave.h"
#include "UObject/Class.h"
#include "AssetData.h"
#include "AudioDevice.h"
#include "AudioDeviceManager.h"



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

	for (int i = 0; i < activeSounds.Num(); i++)
	{
		value = value + 1.0;
	}

	return value;
}