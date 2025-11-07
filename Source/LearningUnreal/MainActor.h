

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainActor.generated.h"

UCLASS()
class LEARNINGUNREAL_API AMainActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMainActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	TObjectPtr<class AR2Actor> Actor;

	UPROPERTY()
	TSubclassOf<AR2Actor> ActorClass; // BP_R2Actor
};
