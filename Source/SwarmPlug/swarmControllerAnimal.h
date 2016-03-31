// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "swarmController.h"
#include "swarmControllerAnimal.generated.h"

/**
*
*/
UCLASS()
class SWARMPLUG_API AswarmControllerAnimal : public AswarmController
{
	GENERATED_BODY()

public:
	AswarmControllerAnimal();


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
		void StopToEat(float tick, AActor* food, AswarmActor* act);
	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		FVector RunFrom(ACharacter* AC, AswarmActor* act);
	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		FVector MoveTo(FVector target, AswarmActor* act);
	UFUNCTION(BlueprintCallable, Category = AnimalBehaviour)
	FVector LocalPoint(AActor* act);
	FVector localpoint;
	FBox box;
	Behaviours StateManager(AswarmActor* act);
	
	bool RunAway(AswarmActor* act, ACharacter* charact);
		void enumSwitch();
	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		void ApplyAnimalFunctions(float tick);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ActorToAvoid)
		ACharacter *player;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimalBehaviour)
		float playerDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimalBehaviour)
		FVector RunMoveTo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimalBehaviour)
		bool scatterOrRetreat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AnimalBehaviour)
		FVector destination;
	
		TArray<AswarmActor*>swarmBehaviour;
	Behaviours* behave;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Food)
		AActor* food;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Target)
		AActor *target;
	FVector targetLocation;
	
		int arraySize;
	float timer = 0;
	float randomNumber;
	///player avoidance multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmVariables)
		float playerAvoidance;
};
