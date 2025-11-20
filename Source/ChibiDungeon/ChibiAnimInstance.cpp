#include "ChibiAnimInstance.h"
#include "ChibiCharacter.h"
#include "GameFramework/Pawn.h"

void UChibiAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	APawn* PawnOwner = TryGetPawnOwner();
	if (PawnOwner != nullptr)
	{
		ChibiCharacter = Cast<AChibiCharacter>(PawnOwner);
	}
}

void UChibiAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (ChibiCharacter == nullptr)
	{
		APawn* PawnOwner = TryGetPawnOwner();
		ChibiCharacter = Cast<AChibiCharacter>(PawnOwner);
	}
	
	if (ChibiCharacter == nullptr)
		return;
	
	FVector Velocity = ChibiCharacter->GetVelocity();
	Velocity.Z = 0.0f;
	
	Speed = Velocity.Size();
}
