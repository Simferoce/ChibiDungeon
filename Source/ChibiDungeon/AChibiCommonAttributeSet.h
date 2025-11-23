// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AChibiCommonAttributeSet.generated.h"

UCLASS()
class CHIBIDUNGEON_API UChibiCommonAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS_BASIC(UChibiCommonAttributeSet, Health);
	
	UPROPERTY(BlueprintReadWrite, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS_BASIC(UChibiCommonAttributeSet, MaxHealth);
	
	UChibiCommonAttributeSet();
};
