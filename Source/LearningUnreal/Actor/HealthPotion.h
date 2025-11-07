

#pragma once

#include "CoreMinimal.h"
#include "Actor/R3Actor.h"
#include "HealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class LEARNINGUNREAL_API AHealthPotion : public AR3Actor
{
	GENERATED_BODY()
	
public:
	AHealthPotion();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;



protected:
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);


	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class USphereComponent> SphereCollider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<class UStaticMeshComponent> StaticMesh;
};
