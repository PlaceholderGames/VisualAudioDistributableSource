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
#include "AudioThread.h"
#include "Containers/Array.h"



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

	DistanceOut = DistanceOut - DistanceTo;
}

void USoundRecogniser::ActiveSoundVector(const FVector& CameraWorldLocation, FVector& SoundVector)
{
	FAudioDevice* audioDevice = GEngine->GetActiveAudioDevice().GetAudioDevice();

	const TArray<FActiveSound*> activeSounds = audioDevice->GetActiveSounds();

	for (int i = 0; i < activeSounds.Num(); i++)
	{
		FActiveSound* soundPtr = activeSounds[i];
		if (soundPtr->bIsPlayingAudio)
		{
			SoundVector = soundPtr->LastLocation;
		}
	}

	SoundVector = SoundVector - CameraWorldLocation;
}

void USoundRecogniser::SimpleActiveSoundVector(FVector& SoundVector)
{
	//FAudioDevice* audioDevice = GEngine->GetActiveAudioDevice().GetAudioDevice();
	//const TArray<FActiveSound*> activeSounds = audioDevice->GetActiveSounds();;
	const TArray<FActiveSound*> activeSounds = GEngine->GetActiveAudioDevice().GetAudioDevice()->GetActiveSounds();
	
	//FAudioThread::RunCommandOnAudioThread([this, audioDevice, &SoundVector]()
	//	{
	//		const TArray<FActiveSound*> tempActiveSounds = audioDevice->GetActiveSounds();
	//		//activeSounds.Emplace() = audioDevice->GetActiveSounds();
	//		//FActiveSound* soundPtr = tempActiveSounds.GetData();
	//		for (int32 i = 0; i != tempActiveSounds.Num(); ++i)
	//		{
	//			FActiveSound* sound = tempActiveSounds[i];
	//			if (sound->bIsPlayingAudio)
	//			{
	//				FAudioThread::RunCommandOnGameThread([this, sound, &SoundVector]()
	//					{

	//						SoundVector = sound->LastLocation;
	//					});
	//			}
	//		}
	//	});

	for (int i = 0; i < activeSounds.Num(); i++)
	{
		FActiveSound* soundPtr = activeSounds[i];
		if (soundPtr->bIsPlayingAudio)
		{
			SoundVector = soundPtr->LastLocation;
		}
	}
}

float USoundRecogniser::ActiveSoundAngle2D(const FVector& CameraVec, const FVector& SoundVector, bool& IsLeft)
{
	float outAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(CameraVec.GetSafeNormal2D(), SoundVector.GetSafeNormal2D())));

	FVector temp = FVector::CrossProduct(CameraVec.GetSafeNormal(), SoundVector.GetSafeNormal());
	//float outAngle = CameraRot.GetManhattanDistance(SoundVector.Rotation());
	if (temp.Z < 0)
		IsLeft = true;
	else
		IsLeft = false;

	return outAngle;
}

/*
check camera rotation instead of location as that may work
*/