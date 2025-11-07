


#include "Actor/R3Actor.h"

// Sets default values
AR3Actor::AR3Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AR3Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AR3Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

