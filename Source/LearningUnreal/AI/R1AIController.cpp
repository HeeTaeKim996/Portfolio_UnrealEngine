


#include "AI/R1AIController.h"
#include "Navigation/PathFollowingComponent.h"

AR1AIController::AR1AIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void AR1AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);


}

void AR1AIController::BeginPlay()
{
	Super::BeginPlay();


#if 0 // 네브메시 포인트 지정 예제
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalLocation(FVector(0.f, 0.f, 0.f));
	MoveRequest.SetAcceptanceRadius(15.f);

	FNavPathSharedPtr NavPath; // ※ 없어도 되지만(아래 MoveTo 도 인자 하나만 해도 가능), 디버깅 용도로 사용
	MoveTo(MoveRequest, OUT &NavPath);

	if (NavPath.IsValid()) // 디버깅 용도
	{
		TArray<FNavPathPoint>& PathPoints = NavPath->GetPathPoints();
		for (const auto& Point : PathPoints)
		{
			const FVector& Location = Point.Location;
			DrawDebugSphere(GetWorld(), Location, 12.f, 12, FColor::Green, false, 10.f);
		}
	}
#endif
}

void AR1AIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
