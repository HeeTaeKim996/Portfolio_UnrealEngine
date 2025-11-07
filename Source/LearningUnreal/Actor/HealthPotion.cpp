


#include "Actor/HealthPotion.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Character/R1Player.h"

AHealthPotion::AHealthPotion()
{
	PrimaryActorTick.bCanEverTick = true;

	
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	RootComponent = SphereCollider;
	

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SphereCollider);


}

void AHealthPotion::BeginPlay()
{
	Super::BeginPlay();

	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnOverlapBegin);
	SphereCollider->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnOverlapEnd);
}

void AHealthPotion::Tick(float DeltaTime)
{
	Super::BeginPlay();
}

void AHealthPotion::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AR1Player* Player = Cast<AR1Player>(OtherActor))
	{
		if (Player->CreatureState == ECreatureState::Dead) return;


		Player->Heal();

		Destroy();
	}


}

void AHealthPotion::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex)
{

}
