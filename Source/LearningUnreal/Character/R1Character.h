

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/R1HighlightInterface.h"
#include "R1Define.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"
#include "R1Character.generated.h"

class UR1AbilitySystemComponent;

UCLASS()
class LEARNINGUNREAL_API AR1Character : public ACharacter, public IR1HighlightInterface, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AR1Character();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void HandleGameplayEvent(FGameplayTag EventTag) {}

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;




public:
	virtual void Highlight() override;
	virtual void UnHighlight() override;


	virtual void OnDamage(int32 Damage, TObjectPtr<AR1Character> from);
	virtual void OnDead(TObjectPtr<AR1Character> from);


	void RefreshHpBarRatio();


public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void InitAbilitySystem();

protected:
	void OnHealthChanged(const struct FOnAttributeChangeData& Data);



protected:
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;
	

public:
	UPROPERTY(BlueprintReadWrite)
	ECreatureState CreatureState = ECreatureState::None;

;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UWidgetComponent> HpBarComponent;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UR1AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UR1AttributeSet> AttributeSet;


public:
	void AddCharacterAbilities();


	UPROPERTY(EditAnywhere, Category = Abilities)
	TArray<TSubclassOf<class UGameplayAbility>> StartupAbilities;


protected:
#if 0 // Obsolate. Moved To R1Player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class USpringArmComponent> SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UCameraComponent> Camera;
#endif
};