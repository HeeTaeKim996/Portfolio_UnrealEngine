


#include "BT/BTTaskNode_Attack.h"
#include "Character/R1Monster.h"
#include "AI/R1AIController.h"
#include "Animation/R1AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	NodeName = TEXT("AttackCharacter");
}

EBTNodeResult::Type UBTTaskNode_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AR1Monster* monster = Cast<AR1Monster>(OwnerComp.GetAIOwner()->GetPawn());

	if (monster->Target == nullptr) return EBTNodeResult::Failed;;

	if (monster->Target->CreatureState == ECreatureState::Dead) return EBTNodeResult::Failed;

	Cast<UR1AnimInstance>(monster->GetMesh()->GetAnimInstance())->SetAttack(true);

	FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(monster->GetActorLocation(), monster->Target->GetActorLocation());
	monster->SetActorRotation(Rotator);

	return EBTNodeResult::Succeeded;
}
