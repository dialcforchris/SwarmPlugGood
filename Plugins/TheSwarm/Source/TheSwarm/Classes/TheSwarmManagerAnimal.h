#pragma once

#include "Engine.h"
#include "TheSwarmManager.h"
#include "TheSwarmManagerAnimal.generated.h"

UCLASS()
class THESWARM_API ATheSwarmManagerAnimal : public ATheSwarmManager
{

	GENERATED_UCLASS_BODY()

public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	////////////////////////////////
	//animal behaviours
	////////////////////////////////

	///go to destination
	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		void AnimalApply(float tick);

	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		FVector RunFrom(ACharacter* AC, ATheSwarmActor* act);

	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		FVector MoveTo(FVector target, ATheSwarmActor* act);

	UFUNCTION(BlueprintCallable, Category = AnimalBehaviour)
		FVector LocalPoint(AActor* act);

		FVector localpoint;
		FBox box;
	UFUNCTION(BlueprintCallable, Category = AnimalBehaviour)
		Behaviours StateManager(ATheSwarmActor* act, float tick);

		float timer = 0;
		bool swtch;
		bool RunAway(ATheSwarmActor* act, ACharacter* charact);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActorToAvoid)
		ACharacter *player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimalBehaviour)
		float playerDistance = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimalBehaviour)
		FVector RunMoveTo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimalBehaviour)
		bool scatterOrRetreat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimalBehaviour)
		FVector destination;
	Behaviours* behave = new Behaviours;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Food)
		AActor* food;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Target)
		AActor *target;
	FVector targetLocation;
	
	int arraySize;

	float randomNumber;
	///player avoidance multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmVariables)
		float playerAvoidance = 10;
};
