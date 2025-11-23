#include "AChibiCharacter.h"
#include "AChibiCommonAttributeSet.h"

AChibiCharacter::AChibiCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	CommonAttributeSet = CreateDefaultSubobject<UChibiCommonAttributeSet>(TEXT("CommonAttributeSet"));
}

void AChibiCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);	
	
	if (AbilitySystemComponent != nullptr)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void AChibiCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	if (AbilitySystemComponent == nullptr)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

UAbilitySystemComponent* AChibiCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
