// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnScript.h"

// Sets default values
AMyPawnScript::AMyPawnScript()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



}

// Called when the game starts or when spawned
void AMyPawnScript::BeginPlay()
{
	Super::BeginPlay();

	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals %f"), GetWorld()->TimeSeconds));
	
	FActiveSound reference;

	MySoundArray.Emplace(reference);
}

// Called every frame
void AMyPawnScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

// Called to bind functionality to input
void AMyPawnScript::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

