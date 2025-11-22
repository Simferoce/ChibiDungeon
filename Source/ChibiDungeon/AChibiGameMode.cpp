#include "AChibiGameMode.h"
#include "AChibiCharacter.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/PlayerController.h"

void AChibiGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);
}
