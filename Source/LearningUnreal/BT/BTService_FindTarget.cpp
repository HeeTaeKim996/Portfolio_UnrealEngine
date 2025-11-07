


#include "BT/BTService_FindTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/R1Character.h"
#include "AI/R1AIController.h"
#include "Character/R1Monster.h"

UBTService_FindTarget::UBTService_FindTarget()
{
	NodeName = TEXT("FindTargetService");
	Interval = 0.5f;
}

void UBTService_FindTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* LocalPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (LocalPawn == nullptr) return;

	UWorld* World = LocalPawn->GetWorld();
	if (World == nullptr) return;



	TArray<FOverlapResult> OverlapResults;
	FVector Location = LocalPawn->GetActorLocation();
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, LocalPawn);

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel12, // ※ 주의. config - 의 ...ini 파일 중 하나에서 채털넘버를 알아야 할 수 있다 함. 오류 조심.
		FCollisionShape::MakeSphere(SearchRadius),
		CollisionQueryParam
	);

	AR1Monster* Monster = Cast<AR1Monster>(LocalPawn);

	if (bResult)
	{
		for (FOverlapResult& OverlapResult : OverlapResults)
		{
			AR1Character* R1Character = Cast<AR1Character>(OverlapResult.GetActor());
			if (R1Character)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetKey.SelectedKeyName, R1Character);
				DrawDebugSphere(World, Location, SearchRadius, 16, FColor::Green, false, 0.2f); // ※ 디버깅 용도

				if (R1Character->CreatureState == ECreatureState::Dead)
				{
					continue;
				}

				Monster->Target = R1Character;

				return;
			}
		}
	}


	OwnerComp.GetBlackboardComponent()->SetValueAsObject(TargetKey.SelectedKeyName, nullptr); // 없는 경우, nullptr 을 반환
	DrawDebugSphere(World, Location, SearchRadius, 16, FColor::Red, false, 0.2f); // ※ 디버깅 용도
	Monster->Target = nullptr;
}
