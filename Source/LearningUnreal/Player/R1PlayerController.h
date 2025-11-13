

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "R1Define.h"
#include "GameplayTagContainer.h"
#include "R1PlayerController.generated.h"

struct FInputActionValue;
class UNiagaraSystem;
class AR1Character;

/**
 * 
 */
UCLASS()
class LEARNINGUNREAL_API AR1PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AR1PlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;

#ifdef USE_TPS_CONTROLL
private:
	void Input_Test(const FInputActionValue& InputValue);
	void Input_Move(const FInputActionValue& InputValue);
	void Input_Turn(const FInputActionValue& InputValue);
	void Input_Jump(const FInputActionValue& InputValue);
	void Input_Attack(const FInputActionValue& InputValue);
#endif

#if 0 // Obsolate
protected:
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> TestAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<class UInputAction> TurnAction;
#endif

private:
	void TickCursorTrace();
	void ChaseTargetAndAttack();

private:
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();


	ECreatureState GetCreatureState();
	void SetCreatureState(ECreatureState InState);

public:
	void HandleGameplayEvent(FGameplayTag eventTag);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UNiagaraSystem> FXCursor;

private:
	FVector CachedDestination;
	float FollowTime;
	bool bMousePressed = false;
	bool isAttacking = false;

private:
	void SetAttack(bool InIsAttacking);
public:
	void TEST_FOR_ABILITY_Attack();

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AR1Character> TargetActor;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AR1Character> HighlightActor;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class AR1Player> R1Player;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<class UR1AnimInstance> PlayerAnim;
};
