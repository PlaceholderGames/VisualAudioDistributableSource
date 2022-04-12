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
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext), Category = "HUD|Util")
		static float ActiveSoundNumber();

	/**
	*Spits out vector of distance from current active sound to given vector
	*
	*@param CameraWorldLocation - vector we want to calculate the distance from
	*@param CameraWorldRotation - Rotator for camera/player
	*
	*@outparam	DistanceOut - vector of distance between the in param and the active sound
	*@outparam  absoluteDistance - pythags of x and y from distanceout
	*@outparam	orientationAngle - FQuat orientation corresponding to the direction in which the vector points
	*@outparam	absoluteAngle - angle of FQuat
	*@outparam	AimAtAngle - calculated angle
	*
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext), Category = "HUD|Util")
		static void ActiveSoundDistanceVector(const FVector& DistanceTo, const FRotator& RotationTo, FVector& DistanceOut, float& absoluteDistance, float& absoluteAngle, FQuat& orientationAngle, float& AimAtAngle);

	/**
	*Spits out vector of distance from current active sound to given vector
	*
	*@param CameraWorldLocation - vector we want to calculate the distance from
	*
	*@outparam	SoundVector - vector of distance between the in param and the active sound
	*
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext), Category = "HUD|Util")
		static void ActiveSoundVector(const FVector& CameraWorldLocation, FVector& SoundVector);



	/**
	*Spits out the number of currently active sounds
	*
	*@param		CameraRot - Rotation of Camera from user
	*@param		SoundVector
	* 
	*@outparam	outAngle - Angle between sound last location and camera rotation
	*@outparam	IsLeft - bool confirming if left or right
	*
	*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", CallableWithoutWorldContext), Category = "HUD|Util")
		static float ActiveSoundAngle2D(const FVector& CameraVec, const FVector& SoundVector, bool& IsLeft);

	/*
	inparam float angle
	inparam float isLeft

	outparam bool topWidget
	outparam bool leftWidget
	outparam bool rightWidget
	outparam bool bottomWidget

	
	*/

};