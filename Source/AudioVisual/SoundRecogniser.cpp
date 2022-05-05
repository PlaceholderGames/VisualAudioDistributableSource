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


float USoundRecogniser::ActiveSoundNumber()
{
	float value = 0.0;

	FAudioDevice* audioDevice = GEngine->GetActiveAudioDevice().GetAudioDevice();

	const TArray<FActiveSound*> activeSounds = audioDevice->GetActiveSounds();

	for (int i = 0; i < activeSounds.Num(); i++)
	{
		FActiveSound* soundPtr = activeSounds[i];
		if (soundPtr->bIsPlayingAudio)
			value = value + 1.0;
	}

	return value;
}

void USoundRecogniser::SimpleActiveSoundVector(FVector& SoundVector)
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
}

/* //DEPRECATED
void USoundRecogniser::ActiveSoundDistanceVector(const FVector& DistanceTo, const FRotator& RotationTo, FVector& DistanceOut, float& absoluteDistance, float& absoluteAngle, FQuat& orientationAngle, float& AimAtAngle)
{
	FAudioDevice* audioDevice = GEngine->GetActiveAudioDevice().GetAudioDevice();

	const TArray<FActiveSound*> activeSounds = audioDevice->GetActiveSounds();

	for (int i = 0; i < activeSounds.Num(); i++)
	{
		FActiveSound* soundPtr = activeSounds[i];
		if (soundPtr->bIsPlayingAudio)
		{
			DistanceOut = soundPtr->LastLocation;
		}
	}

	//orientationAngle = DistanceOut.ToOrientationQuat();
	//absoluteAngle = orientationAngle.GetAngle();

	//FRotator temp = orientationAngle.Rotator();
	//AimAtAngle = ((acosf(FVector::DotProduct(DistanceTo, DistanceOut))) * (180 / 3.1415926));
	//AimAtAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(DistanceTo, DistanceOut)));

	DistanceOut = DistanceOut - DistanceTo;
}*/

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

float USoundRecogniser::ActiveSoundAngle2D(const FVector& CameraVec, const FVector& SoundVector, bool& IsLeft)
{
	float outAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(CameraVec.GetSafeNormal2D(), SoundVector.GetSafeNormal2D())));

	FVector temp = FVector::CrossProduct(CameraVec.GetSafeNormal(), SoundVector.GetSafeNormal());
	if (temp.Z < 0)
		IsLeft = true;
	else
		IsLeft = false;

	return outAngle;
}