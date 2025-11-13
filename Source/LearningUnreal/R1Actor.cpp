


#include "R1Actor.h"
#include "R1Object.h"



// Sets default values
AR1Actor::AR1Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AR1Actor::BeginPlay()
{
	Super::BeginPlay();


#ifdef TEST_UPROPERTY
	obj1 = NewObject<UR1Object>();
	obj2 = NewObject<UR1Object>();
	
		GEngine->ForceGarbageCollection(true);
#endif
}

// Called every frame
void AR1Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (obj1 == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Obj1_Deleted")); 
	}
	
	if (obj2 == nullptr) {}

}

