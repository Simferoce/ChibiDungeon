// cpp
// Source/ChibiDungeon/ChibiGameMode.h
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AChibiCharacter.h"
#include "AChibiGameMode.generated.h"

UCLASS()
class CHIBIDUNGEON_API AChibiGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void PostLogin(APlayerController* NewPlayer) override;
};
