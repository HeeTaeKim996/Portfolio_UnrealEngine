

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "R3Actor.generated.h"

UCLASS()
class LEARNINGUNREAL_API AR3Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AR3Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
