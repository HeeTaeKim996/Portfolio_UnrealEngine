


#include "BT/BTDecorator_IsAlive.h"
#include "AI/R1AIController.h"
#include "Character/R1Character.h"

bool UBTDecorator_IsAlive::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (AR1Character* Character = Cast<AR1Character>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		return Character->CreatureState != ECreatureState::Dead;
	}

	return false;
}
