


#include "Character/R1Character.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "R1Define.h"
#include "Components/WidgetComponent.h"
#include "UI/R1HpBarWidget.h"
#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/R1AttributeSet.h"
#include "Animation/R1AnimInstance.h"
#include "GameplayEffectExtension.h" 

AR1Character::AR1Character()
{
	PrimaryActorTick.bCanEverTick = true;

#if 0 // R1Player 로 이동
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->TargetArmLength = 700.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
#endif 

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));


	HpBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HpBarComponent->SetupAttachment(GetRootComponent());

	ConstructorHelpers::FClassFinder<UUserWidget> HealthBarWidgetClass(
		TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/UI/WBP_HpBar.WBP_HpBar_C'"));
	if (HealthBarWidgetClass.Succeeded())
	{
		HpBarComponent->SetWidgetClass(HealthBarWidgetClass.Class);
		HpBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
		HpBarComponent->SetDrawAtDesiredSize(true);
		HpBarComponent->SetRelativeLocation(FVector(0, 0, 100));
	}
}

void AR1Character::BeginPlay()
{
	Super::BeginPlay();
	
	RefreshHpBarRatio();

	AddCharacterAbilities();
}

void AR1Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AR1Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AR1Character::Highlight()
{
	bHighlighted = true;
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(250);
}

void AR1Character::UnHighlight()
{
	bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
}

void AR1Character::OnDamage(int32 Damage, TObjectPtr<AR1Character> from)
{
	float Hp = AttributeSet->GetHealth();
	float MaxHp = AttributeSet->GetMaxHealth();

	Hp = FMath::Clamp(Hp - Damage, 0, MaxHp);
	AttributeSet->SetHealth(Hp);

	if (Hp == 0)
	{
		OnDead(from);
	}

}

void AR1Character::OnDead(TObjectPtr<AR1Character> from)
{
	if (CreatureState == ECreatureState::Dead) return;

	CreatureState = ECreatureState::Dead;

	Cast<UR1AnimInstance>(GetMesh()->GetAnimInstance())->SetIsAlive(false);

	SetLifeSpan(3.f);
}

void AR1Character::RefreshHpBarRatio()
{
	if (HpBarComponent)
	{
		float Hp = AttributeSet->GetHealth();
		float MaxHp = AttributeSet->GetMaxHealth();

		float Ratio = Hp / MaxHp;
		UR1HpBarWidget* hpBar = Cast<UR1HpBarWidget>(HpBarComponent->GetUserWidgetObject());
		hpBar->SetHpRatio(Ratio);
	}
}


UAbilitySystemComponent* AR1Character::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AR1Character::InitAbilitySystem()
{
}

void AR1Character::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	if (HpBarComponent)
	{
		float Hp = Data.NewValue;
		float MaxHp = AttributeSet->GetMaxHealth();

		if(Hp > MaxHp)
		{
			Hp = MaxHp;
			AttributeSet->SetHealth(Hp);
		}

		float Ratio = Hp / MaxHp;
		UR1HpBarWidget* hpBar = Cast<UR1HpBarWidget>(HpBarComponent->GetUserWidgetObject());
		hpBar->SetHpRatio(Ratio);
	}
}

void AR1Character::AddCharacterAbilities()
{
	UR1AbilitySystemComponent* ASC = Cast<UR1AbilitySystemComponent>(AbilitySystemComponent);

	if (ASC == nullptr) return;

	ASC->AddCharacterAbilities(StartupAbilities);
}


