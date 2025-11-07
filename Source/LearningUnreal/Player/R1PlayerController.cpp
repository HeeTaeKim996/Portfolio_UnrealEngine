


#include "Player/R1PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "System/R1AssetManager.h"
#include "Data/R1InputData.h"
#include "R1GameplayTags.h"
#include "Character/R1Player.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/R1AnimInstance.h"

AR1PlayerController::AR1PlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;



}

void AR1PlayerController::BeginPlay()
{
	Super::BeginPlay();

#if 0 // (초기버전) 블루프린트에 직접 할당
	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->AddMappingContext(InputMappingContext, 0);
	}
#else // AssetManager 사용 버전
	if (const UR1InputData* InputData = UR1AssetManager::GetAssetByName<UR1InputData>("InputData"))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(InputData->InputMappingContext, 0);
		}
	}
#endif

#if 0
	ACharacter* C = Cast<ACharacter>(GetPawn());
	if (C)
	{
		C->GetCharacterMovement()->bUseAccelerationForPathFollowing = true;
	}
#endif


	R1Player = Cast<AR1Player>(GetCharacter());
	PlayerAnim = Cast<UR1AnimInstance>(R1Player->GetMesh()->GetAnimInstance());
}




void AR1PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

#if 0 // (초기버전) 블루프린트에 직접 할당
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(TestAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Test);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ThisClass::Input_Turn);
	}
#else // AssetManager 사용 버전
	if (const UR1InputData* InputData = UR1AssetManager::GetAssetByName<UR1InputData>("InputData"))
	{
		UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

#ifdef USE_TPS_CONTROLL
		auto Action1 = InputData->FindInputActionByTag(R1GameplayTags::Input_Action_Move);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);

		auto Action2 = InputData->FindInputActionByTag(R1GameplayTags::Input_Action_Turn);
		EnhancedInputComponent->BindAction(Action2, ETriggerEvent::Triggered, this, &ThisClass::Input_Turn);

		auto Action3 = InputData->FindInputActionByTag(R1GameplayTags::Input_Action_Jump);
		EnhancedInputComponent->BindAction(Action3, ETriggerEvent::Triggered, this, &ThisClass::Input_Jump);

		auto Action4 = InputData->FindInputActionByTag(R1GameplayTags::Input_Action_Attack);
		EnhancedInputComponent->BindAction(Action4, ETriggerEvent::Triggered, this, &ThisClass::Input_Attack);
#endif

		auto Action1 = InputData->FindInputActionByTag(R1GameplayTags::Input_Action_SetDestination);

		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Started, this, &ThisClass::OnInputStarted);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Triggered, this, &ThisClass::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Completed, this, &ThisClass::OnSetDestinationReleased);
		//EnhancedInputComponent->BindAction(Action1, ETriggerEvent::Canceled, this, &ThisClass::OnSetDestinationReleased);
	}
#endif




}

#ifdef USE_TPS_CONTROLL
void AR1PlayerController::Input_Test(const FInputActionValue& InputValue)
{
	GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Cyan, TEXT("Test"));
}

void AR1PlayerController::Input_Move(const FInputActionValue& InputValue)
{
	FVector2D MovementVector = InputValue.Get<FVector2D>();

	if (MovementVector.X != 0)
	{
#if 0
		FVector Direction = FVector::ForwardVector * MovementVector.X;
		GetPawn()->AddActorWorldOffset(Direction * 50.f);
#else
		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.X); // ※ DeltaTime 은 AddMovementInpt 내부에서 연산되기에, 입력 필요 없음
#endif
	}
	if (MovementVector.Y != 0)
	{
#if 0
		FVector Direction = FVector::RightVector * MovementVector.Y;
		GetPawn()->AddActorWorldOffset(Direction * 50.f);
#else
		FRotator Rotator = GetControlRotation();
		FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0, Rotator.Yaw, 0));
		GetPawn()->AddMovementInput(Direction, MovementVector.Y);
#endif
	}
}

void AR1PlayerController::Input_Turn(const FInputActionValue& InputValue)
{
	float val = InputValue.Get<float>();

	UE_LOG(LogTemp, Log, TEXT("%.6f"), val);

	AddYawInput(val);
}

void AR1PlayerController::Input_Jump(const FInputActionValue& InputValue)
{
	if (AR1Character* R1Player = Cast<AR1Player>(GetPawn()))
	{
		R1Player->Jump();
	}
}

void AR1PlayerController::Input_Attack(const FInputActionValue& InputValue)
{
	UE_LOG(LogTemp, Log, TEXT("Attack Inputed"));
}
#endif


void AR1PlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (R1Player->CreatureState == ECreatureState::Dead) return;

	TickCursorTrace();
	ChaseTargetAndAttack();
}



void AR1PlayerController::TickCursorTrace()
{
	if (bMousePressed) return;

	FHitResult Hit;
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit) == false) return;

	AR1Character* TempHighlightActor = Cast<AR1Character>(Hit.GetActor());
	if (TempHighlightActor == nullptr)
	{
		if (HighlightActor)
		{
			HighlightActor->UnHighlight();
		}
	}
	else
	{
		if (HighlightActor)
		{
			if (HighlightActor != TempHighlightActor)
			{
				HighlightActor->UnHighlight();
				TempHighlightActor->Highlight();
			}
		}
		else
		{
			TempHighlightActor->Highlight();
		}
	}

	HighlightActor = TempHighlightActor;
}

void AR1PlayerController::ChaseTargetAndAttack()
{
	if (TargetActor == nullptr) return;
	if (TargetActor == Cast<AR1Character>(R1Player)) return;
	if (TargetActor->CreatureState == ECreatureState::Dead)
	{
		SetAttack(false);
		return;
	}

	{
		ECreatureState state = GetCreatureState();
		if (state == ECreatureState::Dead) return;
	}

	FVector Direction = TargetActor->GetActorLocation() - R1Player->GetActorLocation();

	float DirLength = Direction.Length();
	if (DirLength < 250.f)
	{



		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Cyan, TEXT("Attack"));


		SetAttack(true);


		FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(R1Player->GetActorLocation(), TargetActor->GetActorLocation());
		R1Player->SetActorRotation(Rotator);


	}
	else
	{
		Direction /= DirLength;
		R1Player->AddMovementInput(Direction, 1.f, false);

		SetAttack(false);
	}
}



void AR1PlayerController::OnInputStarted()
{
	if (R1Player->CreatureState == ECreatureState::Dead) return;

	StopMovement();

	bMousePressed = true;
	TargetActor = HighlightActor;
}

void AR1PlayerController::OnSetDestinationTriggered()
{
	if (R1Player->CreatureState == ECreatureState::Dead) return;
	if (TargetActor) return;

	SetAttack(false);

	FollowTime += GetWorld()->GetDeltaSeconds();

	FHitResult Hit;
	bool bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);

	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	if (R1Player)
	{
		FVector WorldDirection = (CachedDestination - R1Player->GetActorLocation()).GetSafeNormal();
		R1Player->AddMovementInput(WorldDirection, 1.0f, false);
	}



}

void AR1PlayerController::OnSetDestinationReleased()
{
	if (R1Player->CreatureState == ECreatureState::Dead) return;

	bMousePressed = false;



	if (FollowTime <= ShortPressThreshold)
	{
		if (TargetActor == nullptr)
		{
			// ※ 짧게 클릭했을 때, (1) AI 로 해당 장소로 이동 명령을 내리고, (2) 해당 좌표에 FXCursor 를 생성하는 코드
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination); // ※ @@ 네브메시 가 맵에 할당돼야 이동한다!!!
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator,
				FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true); // ※ 현재 블프로 할당된 커서 자체에 문제가 있어서 안보일거다 그냥 무시하고 넘어감
		}
	}

	FollowTime = 0.f;

}

ECreatureState AR1PlayerController::GetCreatureState()
{
	if (R1Player)
	{
		return R1Player->CreatureState;
	}
	return ECreatureState::None;
}


void AR1PlayerController::SetCreatureState(ECreatureState InState)
{
	if (R1Player)
	{
		R1Player->CreatureState = InState;
	}
}

void AR1PlayerController::HandleGameplayEvent(FGameplayTag eventTag)
{
	if (eventTag.MatchesTag(R1GameplayTags::Event_Animation_Attack))
	{
		if (TargetActor)
		{
			TargetActor->OnDamage(50, R1Player);
		}
	}
}

void AR1PlayerController::SetAttack(bool InIsAttacking)
{


	if (isAttacking == InIsAttacking) return;



#if 0 // Ability 공부 목적으로 없애고, ActivateAbility 를 사용하는 구조로
	isAttacking = InIsAttacking;
	if (PlayerAnim)
	{
		PlayerAnim->SetAttack(InIsAttacking);
	}
#else
	isAttacking = InIsAttacking;
	if (InIsAttacking)
	{
		R1Player->ActivateAbility(R1GameplayTags::Ability_Attack); // Ability 공부 목적
	}
	else
	{
		if (PlayerAnim)
		{
			PlayerAnim->SetAttack(false);
		}
	}
#endif
}

void AR1PlayerController::TEST_FOR_ABILITY_Attack()
{
	if (PlayerAnim)
	{
		PlayerAnim->SetAttack(true);
	}
}
