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
#include "Math/Vector.h"



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

void USoundRecogniser::ActiveSoundDistanceVector(const FVector& DistanceTo, const FRotator& RotationTo, FVector& DistanceOut, float& absoluteDistance, float& absoluteAngle, FQuat& orientationAngle, float& AimAtAngle)
{
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

			//if (soundPtr->MaxDistance <= DistanceOut)
			
		}
	}
	/*
	for (auto& i : activeSounds)
	{
		value = value + 1;

	}
	*/
	//DistanceOut = DistanceOut - DistanceTo;
	//orientationAngle = DistanceOut.ToOrientationQuat();
	//absoluteAngle = orientationAngle.GetAngle();

	//FRotator temp = orientationAngle.Rotator();
	//AimAtAngle = ((acosf(FVector::DotProduct(DistanceTo, DistanceOut))) * (180 / 3.1415926));
	//AimAtAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(DistanceTo, DistanceOut)));

	DistanceOut = DistanceTo - DistanceOut;
}

float USoundRecogniser::ActiveSoundAngle2D(const FVector& CameraVec, const FRotator& CameraRot, const FVector& SoundVector)
{
	float outAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(CameraVec.GetSafeNormal2D(), SoundVector.GetSafeNormal2D())));
	//float outAngle = CameraRot.GetManhattanDistance(SoundVector.Rotation());

	return outAngle;
}

/*
check camera rotation instead of location as that may work
*/