#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AChibiAIController.generated.h"

UCLASS()
class CHIBIDUNGEON_API AChibiAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;
	
	void StartWander();
	
	FVector PickRandomPointInCircle() const;
	
	UPROPERTY(EditAnywhere, Category= "Wander")
	float WanderRadius = 300.0f;
	
	UPROPERTY(EditAnywhere, Category= "Wander")
	float WanderSpeed = 100.0f;
	
	UPROPERTY(EditAnywhere, Category= "Wander")
	float WanderMinStopDuration = 1.0f;
	
	UPROPERTY(EditAnywhere, Category= "Wander")
	float WanderMaxStopDuration = 3.0f;
private:
	float DefaultWalkSpeed;
	FVector WanderCenter;
	FTimerHandle WanderTimerHandle;
};
