

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsAlive.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGUNREAL_API UBTDecorator_IsAlive : public UBTDecorator
{
	GENERATED_BODY()
	

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
