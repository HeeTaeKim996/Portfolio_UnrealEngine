


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
	
		GEngine->ForceGarbageCollection(true); // 필드멤버 UObject 를 UPROPERTY 선언하지 않았다면, 해당 필드멤버를 수거하는 것을 보여주기 위한 코드
#endif
}

// Called every frame
void AR1Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (obj1 == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Obj1_Deleted")); 
		// GC가 수거해가도, obj1 == nullptr은 안찍힘 (obj2 와 다르게, Name 이 null. GC 에 의해 삭제됐지만, 포인터는 유효). 메모리 오염될 수 있기에 치명적 
	}
	
	if (obj2 == nullptr) {} // UPROPERTY() 로 선언됐기에, GC의 수거대상이 아님

}

