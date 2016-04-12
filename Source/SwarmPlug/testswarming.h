// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "testswarming.generated.h"

/**
 * 
 */
UCLASS()
class SWARMPLUG_API Utestswarming : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		Utestswarming();
public:
			UFUNCTION(BlueprintCallable, meta = (DisplayName = "Execute Sample function", Keywords = "Swarming sample test testing"), Category = "SwarmingTesting")
			static float SwarmingSampleFunction(float Param);
		
			UFUNCTION(BlueprintCallable, meta = (DisplayName = "Separation", Keywords = "Flocking Swarm AI"), Category = "Swarming")
			static	FVector Separation(AActor* act, AActor* agent);
		
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Alignment", Keywords = "Flocking Swarm AI"), Category = "Swarming")
			static FVector Alignment(AActor* act, AActor* agent);
		//
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Cohesion", Keywords = "Flocking Swarm AI"), Category = "Swarming")
			static FVector Cohesion(AActor* act, AActor* agent);
		
		//Applies a basic swarming algorithm
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Apply Boids", Keywords = "Flocking Swarm AI"), Category = "Insect Swarming")
			static void ApplyBasicSwarming(float EventTick, TArray<AActor*>swarmArray, TArray<FVector> velocityArray, bool canFly, TArray<AActor*>&outActors,
			TArray<FVector>&outVelocities, float separationWeight = 1.0f, float alignmentWeight = 0.1f, float cohesionWeight = 0.1f, bool separationOn = true,
			bool alignmentOn = true, bool cohesionOn = true, float maxAgentDistance = 500.0f,float speed = 1.0f);
		
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Swarm", Keywords = "Flocking Swarm AI"), Category = "Swarming")
			static void CreateSwarm(UClass* agentClass, bool canFly, TArray<AActor*>& swarmArray, TArray<FVector>& velocityArray,
			int32 swarmSize = 10, float minMaxX = 1000.0f, float minMaxY = 1000.0f, float maxZ = 800.0f);
	
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Locations", Keywords = "Flocking Swarm AI"), Category = "Insect Swarming")
			static void SetLocation(TArray<FVector>velArray, TArray<AActor*>actors,float tick);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Distance", Keywords = "Flocking Swarm AI"), Category = "Swarming")
			static float GetDistance(AActor* act, AActor* agent);
		
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Cone Trace", Keywords = "Flocking Swarm AI"), Category = "Swarming")
			static FHitResult ConeTrace(AActor* act, float radius = 1.0f, float traceLength = 200.0f,
			bool renderConeTrace = true, bool canFly = false);

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Trace Avoidance", Keywords = "Flocking Swarm AI"), Category = "Swarming")
			static FVector Avoidance(FHitResult hit);
		
		
			
};

