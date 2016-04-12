#pragma once

#include "Engine.h"
#include "TheSwarmActor.generated.h"

UCLASS()
class THESWARM_API ATheSwarmActor : public AActor
{

	GENERATED_UCLASS_BODY()

public:
//	ATheSwarmActor(const class FPostConstructInitializeProperties& PCIP);


 // Called when the game starts or when spawned
 virtual void BeginPlay() override;

 // Called every frame
 virtual void Tick(float DeltaSeconds) override;

 //Actor Velocity
 UPROPERTY(EditAnywhere, BlueprintReadWrite)
	 FVector velocity;

 enum Behaviours behave;
 
 UPROPERTY(EditAnywhere, BlueprintReadWrite)
	 UClass* swarmClass;

 AActor* actor;

 UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
	 void SpawnActors(UClass* cl);

};

UENUM()
enum Behaviours
{
	IDLE,
	MOVETOTARGET,
	WAIT,
	RUN,
	FLOCK,
	FOLLOW
};