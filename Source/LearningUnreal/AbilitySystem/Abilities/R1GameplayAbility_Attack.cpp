


#include "AbilitySystem/Abilities/R1GameplayAbility_Attack.h"
#include "Character/R1Player.h"
#include "Animation/R1AnimInstance.h"
#include "R1GameplayTags.h"
#include "Player/R1PlayerController.h"
#include "Character/R1Player.h"

UR1GameplayAbility_Attack::UR1GameplayAbility_Attack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

bool UR1GameplayAbility_Attack::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) == false)
	{
		return false;
	}

	return true;
}

void UR1GameplayAbility_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	AR1Player* Player = Cast<AR1Player>(ActorInfo->AvatarActor);
	Cast<AR1PlayerController>(Player->Controller)->TEST_FOR_ABILITY_Attack();


}

void UR1GameplayAbility_Attack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
