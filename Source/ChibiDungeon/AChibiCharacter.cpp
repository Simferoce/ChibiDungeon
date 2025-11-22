#include "AChibiCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AChibiCharacter::AChibiCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationYaw = false;
	if (UCharacterMovementComponent* MovementComponent = GetCharacterMovement())
	{
		MovementComponent->bOrientRotationToMovement = true;
		MovementComponent->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	}
}

void AChibiCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AChibiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Delta = TargetLocation - GetCapsuleComponent()->GetComponentLocation();
	Delta.Z = 0.0f;

	if (bMovingToLocation && Delta.Size() < 10.0f)
	{
		bMovingToLocation = false;
		UE_LOG(LogTemp, Log, TEXT("Reached Target Location"));
	}
	else if (bMovingToLocation)
	{
		FVector Direction = Delta.GetSafeNormal();
		AddMovementInput(Direction);
		UE_LOG(LogTemp, Log, TEXT("Moving to Target Location (%s)"), *Delta.ToString());
	}
}

void AChibiCharacter::MoveTo(const FVector& Destination)
{
	TargetLocation = Destination;
	bMovingToLocation = true;
	UE_LOG(LogTemp, Log, TEXT("MoveTo called on %s -> %s"), *GetName(), *Destination.ToString());
	DrawDebugSphere(GetWorld(), Destination, 10.0f, 12, FColor::Red, false, 1.0f);
}