


#include "Character/R1Monster.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/R1MonsterSet.h"
#include "Actor/HealthPotion.h"

AR1Monster::AR1Monster()
{
	PrimaryActorTick.bCanEverTick = true;


	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -88.f), FRotator(0, -90.f, 0));

	AbilitySystemComponent = CreateDefaultSubobject<UR1AbilitySystemComponent>("AbilitySystemComponent");

	AttributeSet = CreateDefaultSubobject<UR1MonsterSet>("MonsterSet");
}

void AR1Monster::BeginPlay()
{
	Super::BeginPlay();

	InitAbilitySystem();
}

void AR1Monster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	FVector SpawnLocation = GetActorLocation() - GetActorForwardVector() * 190.f; // Backward 190
	FRotator SpawnRotation = GetActorRotation();

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<AHealthPotion>(
		HealthPotion,
		SpawnLocation,
		SpawnRotation,
		Params
	);
}

void AR1Monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AR1Monster::InitAbilitySystem()
{
	Super::InitAbilitySystem();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		UR1AttributeSet::GetHealthAttribute()
	).AddUObject(this, &ThisClass::OnHealthChanged);
}



void AR1Monster::HandleGameplayEvent(FGameplayTag EventTag)
{
	if (Target)
	{
		Target->OnDamage(40, Cast<AR1Character>(this));
	}
}