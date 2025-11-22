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

protected:
	virtual void BeginPlay() override;

};