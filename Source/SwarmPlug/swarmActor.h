// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "swarmActor.generated.h"

UCLASS()

class SWARMPLUG_API AswarmActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AswarmActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	//Actor Velocity
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector velocity;
	//Adjust Rotation
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float skRotAdj;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* mesh;
	enum Behaviours behave;


};
enum Behaviours
{
	IDLE,
	MOVETOTARGET,
	WAIT,
	RUN,
	FLOCK,
	FOLLOW

};

