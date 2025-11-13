

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "R1Actor.generated.h"

class UR1Object;



#define TEST_UPROPERTY


UCLASS()
class LEARNINGUNREAL_API AR1Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AR1Actor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
#ifdef TEST_UPROPERTY
	UR1Object* obj1;

	UR1Object* obj2;
#endif

protected:
	UPROPERTY(VisibleAnywhere)
	int32 Hp = 100;
	UPROPERTY(EditAnywhere)
	int32 Mp = 50;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat)
	float Speed = 3.5f;
};
