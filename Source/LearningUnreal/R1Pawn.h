

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "R1Pawn.generated.h"

UCLASS()
class LEARNINGUNREAL_API AR1Pawn : public APawn
{
	GENERATED_BODY()

public:
	AR1Pawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



protected:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCapsuleComponent> CapsuleComponent;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USkeletalMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UFloatingPawnMovement> Movement;
};
