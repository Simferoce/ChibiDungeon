#include "AChibiPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AChibiCharacter.h"
#include "Engine/LocalPlayer.h"
#include "DrawDebugHelpers.h"

void AChibiPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Show mouse and set input mode
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;

    FInputModeGameAndUI InputMode;
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    InputMode.SetHideCursorDuringCapture(false);
    SetInputMode(InputMode);

    // Register mapping context for Enhanced Input
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (DefaultMappingContext)
            {
                Subsystem->AddMappingContext(DefaultMappingContext, 0);
                UE_LOG(LogTemp, Log, TEXT("Added DefaultMappingContext to subsystem for controller %s"), *GetName());
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("DefaultMappingContext is null on controller %s"), *GetName());
            }
        }
    }
}

void AChibiPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
    {
        if (MoveToAction)
        {
            EnhancedInput->BindAction(MoveToAction, ETriggerEvent::Triggered, this, &AChibiPlayerController::OnMoveToAction);
            UE_LOG(LogTemp, Log, TEXT("Bound MoveToAction on controller %s"), *GetName());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("MoveToAction is null on controller %s"), *GetName());
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("InputComponent is not UEnhancedInputComponent on controller %s"), *GetName());
    }
}

void AChibiPlayerController::OnMoveToAction(const FInputActionValue& Value)
{
    FVector WorldLocation;
    FVector WorldDirection;
    if (!DeprojectMousePositionToWorld(WorldLocation, WorldDirection))
        return;

    FVector PlanePoint = FVector::ZeroVector;
    FVector PlaneNormal = FVector::UpVector;

    float Dot = FVector::DotProduct(PlaneNormal, WorldDirection);
    if (FMath::IsNearlyZero(Dot))
        return;

    float Distance = FVector::DotProduct(PlanePoint - WorldLocation, PlaneNormal) / Dot;
    FVector Hit = WorldLocation + WorldDirection * Distance;

    DrawDebugSphere(GetWorld(), Hit, 10.0f, 12, FColor::Green, false, 1.0f);

    if (APawn* P = GetPawn())
    {
        if (AChibiCharacter* Ch = Cast<AChibiCharacter>(P))
        {
            Ch->MoveTo(Hit);
        }
    }
}