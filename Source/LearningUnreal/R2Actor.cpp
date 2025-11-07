


#include "R2Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

AR2Actor::AR2Actor()
{
	PrimaryActorTick.bCanEverTick = true;


	{ // BP 가 아닌, 에셋 할당 하드코딩 방법
#if 0
		Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));

		ConstructorHelpers::FObjectFinder<UStaticMesh> FindMesh(TEXT(
			"/Script/Engine.StaticMesh'/Game/_Arts/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'"));
		// ※ 에셋 우클릭 후 CopyFilePath 하거나, 에셋 클릭후 Ctrl + C 하면 경로 복사됨
		if (FindMesh.Succeeded())
		{
			Body->SetStaticMesh(FindMesh.Object);
		}
#elif 1
		Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
		RootComponent = Body;
		Body->SetRelativeScale3D(FVector(2, 3, 0.5f));

		Wing = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wing"));
		Wing->SetupAttachment(Body);
		Wing->SetRelativeLocationAndRotation(FVector(55, -72, 80), FRotator(0, 90, 0));
		Wing->SetRelativeScale3D(FVector(3.75f, 0.25f, 0.5f));

		Head = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"));
		Head->SetupAttachment(Body);
		Head->SetRelativeLocationAndRotation(FVector(105, 36, 48), FRotator(0, 0, 0));
		Head->SetRelativeScale3D(FVector(0.25f, 0.25f, 0.25f));

		ConstructorHelpers::FObjectFinder<UStaticMesh> FindMesh(TEXT(
			"/Script/Engine.StaticMesh'/Game/_Arts/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'"));
		if (FindMesh.Succeeded())
		{
			Body->SetStaticMesh(FindMesh.Object);
			Wing->SetStaticMesh(FindMesh.Object);
			Head->SetStaticMesh(FindMesh.Object);
		}
#endif
	}
}

void AR2Actor::BeginPlay()
{
	Super::BeginPlay();
	
#if 0
	UGameplayStatics::GetActorOfClass(GetWorld(), AR2Actor::StaticClass()); // ※ == FindObjectOfType
#elif 1
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Harry"), Actors); //

	if (Actors.Num() > 0)
	{
		Target = Actors[0];
	}
#endif
}

void AR2Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#if 0
	FVector NewLocation = GetActorLocation() + FVector::ForwardVector * 50.f * DeltaTime ;
	SetActorLocation(NewLocation);
#elif 0
	AddActorWorldOffset(FVector::ForwardVector * 50.f * DeltaTime);

#elif 1
	if (Target != nullptr)
	{
		FVector dir = Target->GetActorLocation() - GetActorLocation();
		dir.Normalize();

		AddActorWorldOffset(dir * 50.f * DeltaTime);
	}

#endif
}

