

#pragma once

#include "CoreMinimal.h"



UENUM(BlueprintType)
enum class ECreatureState : uint8
{
	None,
	Normal,

	Dead,
};

#define D(x) if(GEngine) { GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, x);}