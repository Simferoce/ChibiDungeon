#include "AChibiCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AChibiCharacter::AChibiCharacter()
{
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