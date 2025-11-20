#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ChibiAnimInstance.generated.h"

UCLASS()
class CHIBIDUNGEON_API UChibiAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	float Speed = 0.f;
	
protected:
	class AChibiCharacter* ChibiCharacter = nullptr;
};
