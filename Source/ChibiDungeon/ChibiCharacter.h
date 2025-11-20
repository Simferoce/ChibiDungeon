// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputSubsystems.h"
#include "ChibiCharacter.generated.h"

UCLASS()
class CHIBIDUNGEON_API AChibiCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AChibiCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveToAction;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool GetMouseRayHitOnGround(FVector& hit);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnMoveToAction(const FInputActionValue& Value);
private:
	
	bool bMovingToLocation = false;
	FVector TargetLocation;
};
