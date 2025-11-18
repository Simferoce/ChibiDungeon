// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnhancedInputSubsystems.h"
#include "ChibiCharacter.generated.h"

UCLASS()
class CHIBIDUNGEON_API AChibiCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AChibiCharacter();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	ACameraActor* CameraActor = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Speed = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveToAction;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool GetMouseRayHitOnGround(FVector& hit);

	UPROPERTY()
	USceneComponent* Root;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnMoveToAction(const FInputActionValue& Value);
private:
	
	FVector TargetLocation;
};
