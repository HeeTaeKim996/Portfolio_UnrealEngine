


#include "MainActor.h"
#include "R2Actor.h"

AMainActor::AMainActor()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<AR2Actor> FindClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprints/BP_R2Actor.BP_R2Actor_C'"));
	// ※  @@@ BP 의 경우 주소 복붙만 하면 못읽음. 주소 끝 (' 전) 에 _C 추가 필요 @@@
	if (FindClass.Succeeded())
	{
		ActorClass = FindClass.Class;
	}
}

void AMainActor::BeginPlay()
{
	Super::BeginPlay();
	
	FVector Location(0, 0, 0);
	FRotator Rotation(0, 0, 0);


#if 0
	 Actor = GetWorld()->SpawnActor<AR2Actor>(Location, Rotation);
#else
	Actor = Cast<AR2Actor>(GetWorld()->SpawnActor(ActorClass));
#endif

	Actor->SetLifeSpan(2.f);
	//GetWorld()->DestroyActor(R2Actor);
}

void AMainActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	
}

