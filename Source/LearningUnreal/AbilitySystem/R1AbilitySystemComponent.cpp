


#include "AbilitySystem/R1AbilitySystemComponent.h"
#include "R1GameplayTags.h"

void UR1AbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<class UGameplayAbility>>& StartupAbilities)
{
	for (auto& AbilityClass : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);

		FGameplayAbilitySpecHandle SpecHandle = GiveAbility(AbilitySpec);
		

		auto& a = ActivatableAbilities;

		//TryActivateAbility(SpecHandle);
		//GiveAbilityAndActivateOnce(AbilitySpec);

		SpecHandles.Add(SpecHandle);
	}
}

void UR1AbilitySystemComponent::ActivateAbility(FGameplayTag AbilityTag)
{
	for (FGameplayAbilitySpecHandle& SpecHandle : SpecHandles)
	{

		if (AbilityTag == R1GameplayTags::Ability_Attack)
		{
			TryActivateAbility(SpecHandle);
		}
	}
}
