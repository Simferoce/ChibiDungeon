// Fill out your copyright notice in the Description page of Project Settings.


#include "ChibiCharacter.h"

// Sets default values
AChibiCharacter::AChibiCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChibiCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChibiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AChibiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

