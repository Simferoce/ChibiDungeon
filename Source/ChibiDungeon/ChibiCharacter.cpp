// Fill out your copyright notice in the Description page of Project Settings.


#include "ChibiCharacter.h"
#include "DrawDebugHelpers.h"

// Sets default values
AChibiCharacter::AChibiCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
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

	FVector hit;
	if(GetMouseRayHitOnGround(hit))
		UE_LOG(LogTemp, Log, TEXT("Hit at %s"), *hit.ToString())
}

// Called to bind functionality to input
void AChibiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AChibiCharacter::GetMouseRayHitOnGround(FVector& hit)
{
	AController* controller = GetController();
	ensure(controller != nullptr);

	APlayerController* playerController = Cast<APlayerController>(controller);
	ensure(playerController != nullptr);

	FVector worldOrigin;
	FVector worldDirection;
	if (!playerController->DeprojectMousePositionToWorld(worldOrigin, worldDirection))
		return false;

	FVector planePoint = FVector(0,0,0);
	FVector planeNormal = FVector(0, 0, 1);

	float dot = FVector::DotProduct(planeNormal, worldDirection);
	if (FMath::IsNearlyZero(dot))
		return false;

	float distance = FVector::DotProduct(planePoint -  worldOrigin, planeNormal) / dot;
	hit = worldOrigin + worldDirection * distance;

	DrawDebugSphere(GetWorld(), hit, 10.0f, 12, FColor::Red, false, 0.1f);
	return true;
}

