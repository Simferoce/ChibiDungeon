// Fill out your copyright notice in the Description page of Project Settings.

#include "ChibiCharacter.h"
#include "DrawDebugHelpers.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraActor.h"

// Sets default values
AChibiCharacter::AChibiCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
}

// Called when the game starts or when spawned
void AChibiCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Register mapping context with the Enhanced Input subsystem
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
		
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);
		PlayerController->SetInputMode(InputMode);
		
		PlayerController->SetViewTarget(CameraActor);
		PlayerController->bAutoManageActiveCameraTarget = false;
		
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (DefaultMappingContext)
				{
					Subsystem->AddMappingContext(DefaultMappingContext, 0);
					UE_LOG(LogTemp, Log, TEXT("Added DefaultMappingContext to subsystem for %s"), *GetName());
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("DefaultMappingContext is null on %s"), *GetName());
				}
			}
		}
	}
}

// Called to bind functionality to input
void AChibiCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveToAction)
		{
			enhancedInputComponent->BindAction(MoveToAction, ETriggerEvent::Started, this, &AChibiCharacter::OnMoveToAction);
			UE_LOG(LogTemp, Log, TEXT("Bound MoveToAction on %s"), *GetName());
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("MoveToAction is null on %s"), *GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerInputComponent is not UEnhancedInputComponent on %s"), *GetName());
	}
}

// Called every frame
void AChibiCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Delta = TargetLocation - GetActorLocation();
	Delta.Z = 0.0f;

	if (Delta.Size() < 1.0f)
		return;

	FVector Direction = Delta.GetSafeNormal();
	FVector NewPosition = GetActorLocation() + Direction * DeltaTime * Speed;
	UE_LOG(LogTemp, Log, TEXT("Moving from %s to %s."), *NewPosition.ToString(), *GetActorLocation().ToString())
	SetActorLocation(NewPosition);
	//FVector NewPosition = GetActorLocation() + Delta.GetSafeNormal() * Delta.Size();
	//SetActorLocation(NewPosition);
}

bool AChibiCharacter::GetMouseRayHitOnGround(FVector& hit)
{
	AController* controller = GetController();
	ensure(controller != nullptr);

	APlayerController* playerController = Cast<APlayerController>(controller);
	ensure(playerController != nullptr);

	FVector WorldLocation;
	FVector WorldDirection;
	if (!playerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
		return false;

	FVector PlanePoint = FVector(0,0,0);
	FVector PlaneNormal = FVector(0, 0, 1);

	float Dot = FVector::DotProduct(PlaneNormal, WorldDirection);
	if (FMath::IsNearlyZero(Dot))
		return false;

	float Distance = FVector::DotProduct(PlanePoint -  WorldLocation, PlaneNormal) / Dot;
	hit = WorldLocation + WorldDirection * Distance;

	UE_LOG(LogTemp, Log, TEXT("Hit at %s"), *hit.ToString())
	DrawDebugSphere(GetWorld(), hit, 10.0f, 12, FColor::Red, false, 0.1f);
	return true;
}

void AChibiCharacter::OnMoveToAction(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("Move to Mouse"))

	FVector Hit;
	if (GetMouseRayHitOnGround(Hit))
	{
		TargetLocation = Hit;
	}
}