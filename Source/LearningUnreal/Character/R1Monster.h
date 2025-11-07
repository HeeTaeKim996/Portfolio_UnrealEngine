

#pragma once

#include "CoreMinimal.h"
#include "Character/R1Character.h"
#include "R1Monster.generated.h"


/**
 * 
 */
UCLASS()
class LEARNINGUNREAL_API AR1Monster : public AR1Character
{
	GENERATED_BODY()
	
public:
	AR1Monster();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void Tick(float DeltaTime) override;


public:
	virtual void InitAbilitySystem() override;


public:
	virtual void HandleGameplayEvent(FGameplayTag EventTag) override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class AR1Character> Target;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AHealthPotion> HealthPotion;
};
