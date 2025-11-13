


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


#if 0 
	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalLocation(FVector(0.f, 0.f, 0.f));
	MoveRequest.SetAcceptanceRadius(15.f);

	FNavPathSharedPtr NavPath; 
	MoveTo(MoveRequest, OUT &NavPath);

	if (NavPath.IsValid()) 
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
