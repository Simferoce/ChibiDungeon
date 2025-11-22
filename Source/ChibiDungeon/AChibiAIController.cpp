#include "AChibiAIController.h"
#include "AChibiCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void AChibiAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (InPawn != nullptr)
	{
		WanderCenter = InPawn->GetActorLocation();
		
		StartWander();
	}
}

FVector AChibiAIController::PickRandomPointInCircle() const
{
	FVector2D RandomPoint = FMath::RandPointInCircle(WanderRadius);
	return WanderCenter + FVector(RandomPoint.X, RandomPoint.Y, 0.f);
}

void AChibiAIController::StartWander()
{
	APawn* ControlledPawn = GetPawn();
	if(ControlledPawn == nullptr)
		return;
	
	AChibiCharacter* ControlledCharacter = Cast<AChibiCharacter>(ControlledPawn);
	if (ControlledCharacter == nullptr)
		return;
	
	ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = WanderSpeed;
	const FVector Destination = PickRandomPointInCircle();
	
	MoveToLocation(Destination, 50, true, true, true, false);
}

void AChibiAIController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	
	const float WaitTime = FMath::FRandRange(WanderMinStopDuration, WanderMaxStopDuration);
	GetWorldTimerManager().SetTimer(WanderTimerHandle, this, &AChibiAIController::StartWander, WaitTime, false);
}
