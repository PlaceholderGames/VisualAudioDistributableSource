// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Audio.h"
#include "ActiveSound.h"
#include "IAudioExtensionPlugin.h"
#include "SoundDefinitions.h"
#include "IAudioModulation.h"
#include "MyPawnScript.generated.h"


UCLASS()
class AUDIOVISUAL_API AMyPawnScript : public APawn
{
	GENERATED_BODY()

	//UPROPERTY()
		//struct FActiveSound& MySound;
		//struct soundArray[];

public:	
	// Sets default values for this pawn's properties
	AMyPawnScript();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	TArray<FActiveSound> MySoundArray;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
