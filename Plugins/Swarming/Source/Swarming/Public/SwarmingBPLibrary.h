#pragma once
#include "Engine.h"

#include "SwarmingBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class USwarmingBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

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
		bool alignmentOn = true, bool cohesionOn = true, float maxAgentDistance = 500.0f, float speed = 1.0f);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Create Swarm", Keywords = "Flocking Swarm AI"), Category = "Swarming")
		static void CreateSwarm(UClass* agentClass, bool canFly, TArray<AActor*>& swarmArray, TArray<FVector>& velocityArray,
		int32 swarmSize = 10, float minMaxX = 1000.0f, float minMaxY = 1000.0f, float maxZ = 800.0f);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Locations", Keywords = "Flocking Swarm AI"), Category = "Insect Swarming")
		static void SetLocation(TArray<FVector>velArray, TArray<AActor*>actors, float tick);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Distance", Keywords = "Flocking Swarm AI"), Category = "Swarming")
		static float GetDistance(AActor* act, AActor* agent);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Cone Trace", Keywords = "Flocking Swarm AI"), Category = "Swarming")
		static FHitResult ConeTrace(AActor* act, float radius = 1.0f, float traceLength = 200.0f,
		bool renderConeTrace = true, bool canFly = false);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Trace Avoidance", Keywords = "Flocking Swarm AI"), Category = "Swarming")
		static FVector Avoidance(FHitResult hit);
	
};

