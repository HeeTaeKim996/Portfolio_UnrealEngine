

#pragma once

#include "NativeGameplayTags.h"

// ※ @@@ Build.cs 에 모듈 GameplayTags 추가 필요
// Edit - ProjectSettings - Project - GameplayTags 에서 등록 잘 됐는지 확인 가능

namespace R1GameplayTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Move);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Turn);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Jump);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_Attack);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Input_Action_SetDestination);

	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Animation_Begin);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Animation_End);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Animation_Attack);


	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Attack);
}