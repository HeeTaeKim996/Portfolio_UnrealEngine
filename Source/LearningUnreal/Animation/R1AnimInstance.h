

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "R1AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGUNREAL_API UR1AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
		
public:
	UR1AnimInstance(const FObjectInitializer& ObjectIntializer = FObjectInitializer::Get());

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


public:
	UFUNCTION(BlueprintCallable)
	void SetAttack(bool InIsAttacking) { isAttacking = InIsAttacking; }
	void SetIsAlive(bool InIsAlive) { IsAlive = InIsAlive; }

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AR1Character> Character;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UCharacterMovementComponent> MovementComponent;

protected:
	UPROPERTY(BlueprintReadOnly)
	FVector Velocity = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly)
	float GroundSpeed = 0.f;
	UPROPERTY(BlueprintReadOnly)
	bool bShouldMove = false;
	UPROPERTY(BlueprintReadOnly)
	bool bIsFalling = false;
	UPROPERTY(BlueprintReadOnly)
	bool isAttacking = false;
	UPROPERTY(BlueprintReadOnly)
	bool IsAlive = true;
};
