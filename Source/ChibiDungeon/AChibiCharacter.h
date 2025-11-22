#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AChibiCharacter.generated.h"

UCLASS(Blueprintable)
class CHIBIDUNGEON_API AChibiCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AChibiCharacter();

	// Public API used by controller to command movement
	void MoveTo(const FVector& Destination);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool bMovingToLocation = false;
	FVector TargetLocation;
};