// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "swarmActor.h"
#include "swarmController.generated.h"


UCLASS()
class SWARMPLUG_API AswarmController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AswarmController();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/////////////////////////////////////
	////////////Swarm Variables
	/////////////////////////////////////

	//Array containing the swam agents
	UPROPERTY(BlueprintReadOnly)
		TArray <AswarmActor*> swarmArray;
	TArray<FVector> velArray;
	FVector velocity;
	//The size of the swarm
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 swarmSize = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 maxDist = 500;
	//function scalar
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float scaleCoh = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float scaleSep = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float scaleAli = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float speed = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boundaries)
		float MaxX = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boundaries)
		float MinX = -1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boundaries)
		float MaxY = 1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boundaries)
		float MinY = -1000;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boundaries)
		bool canFly;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boundaries)
		float MaxZ = 500;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boundaries)
		float MinZ = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boundaries)
		float boundaryFix = 500;
	//The Actor Class used in the swarm
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmActor)
		TSubclassOf<AActor> ActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmActor)
		UClass* AgentClass;
	//Swarm Actor
	AswarmActor* SwAct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		FVector sep;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		FVector ali;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		FVector coh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		FVector Bound;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
		FVector totalV;
	FVector* ali2;
	int N;
	//////////////////////////////
	//////////////Swarm Functions
	//////////////////////////////

	//Makes Swarm
	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		void CreateSwarm();
	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		void AddRemoveAgents();
	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		FHitResult ConeTracer(AswarmActor* act, ECollisionChannel channel);
	//UPROPERTY(BlueprintReadWrite)
	int32 agents;
		FHitResult hit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmFunctions)
		bool renderConeTrace = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmFunctions)
		float traceLength = 200;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmFunctions)
		float radius;
	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		FVector Collision(FHitResult hit);
	//Swarm Cohesion
	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		FVector cohesion(AswarmActor* b,float dist, AswarmActor* a);
	//Swarm Separation
	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		FVector separation(AswarmActor* b,float dist, AswarmActor* a);
	//Swarm Alignment
	
	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		FVector alignment(AswarmActor* b,float dist,AswarmActor* a);
	
	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		FVector Boundaries(AswarmActor* b);
	//UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		//float Scatter(AswarmActor* b);
	//Apply Basic Swarm Intelligence
	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		void ApplyBasicSwarming(float tick);
	
	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		float GetDistance(AActor* a, AActor* b);

	/*UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
		FVector Avoidance(AActor* act);*/
	//nearestN stuff
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = SwarmFunctions)
	int32 nearestN = 5;
	TArray<AswarmActor*>distArray;
	TArray<float>eachDist;
	void GetDist(AswarmActor* b);
	void SortByDist();
	////////////////////////////
	////bools to pick functions
	/////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmFunctions)
		bool CohesionOn = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmFunctions)
		bool AlignmentOn = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmFunctions)
		bool SeparationOn = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmFunctions)
		bool BoundariesOn = true;

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
		























































FVector alignmentTwo(FVector b);
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ClassForSwarm)
		TSubclassOf<class AActor> aActorClass;
	//////////////////////////////////////////
	/////////////////////////class test stuff
	////////////////////////////////////////////
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ClassForSwarm)
	//UBlueprint* theClass;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector* assignedVec;
	TArray<AActor*>actArray;
	TMap<AActor*, FVector*> theMap;
	void spawnfromclass();
	AActor* classAct;
	FVector ClCohesion(AswarmActor* b);
	FVector ClSeparation(AswarmActor* b);
	FVector ClAlignment(AswarmActor* b);
	FVector ClBoundaries(AswarmActor* b);
	void ClApply(float tick);
	void ClMovement(float tick);
	


};
//
//// Fill out your copyright notice in the Description page of Project Settings.
//
//#pragma once
//
//#include "GameFramework/Actor.h"
//#include "swarmActor.h"
//#include "swarmController.generated.h"
//
//
//UCLASS()
//class SWARMPLUG_API AswarmController : public AActor
//{
//	GENERATED_BODY()
//	
//public:	
//	// Sets default values for this actor's properties
//	AswarmController();
//
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//	
//	// Called every frame
//	virtual void Tick( float DeltaSeconds ) override;
//
//	/////////////////////////////////////
//	////////////Swarm Variables
//	/////////////////////////////////////
//	
//	//Array containing the swam agents
//	UPROPERTY(BlueprintReadOnly)
//		TArray <AswarmActor*> swarmArray;
//	TArray<FVector> velArray;
//	FVector velocity;
//		//The size of the swarm
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		int32 swarmSize;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		int32 maxDist;
//	//function scalar
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		int32 scaleCoh;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		int32 scaleSep;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		int32 scaleAli;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		float speed;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boundaries)
//		float MaxX;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boundaries)
//		float MinX;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boundaries)
//		float MaxY;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boundaries)
//		float MinY;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boundaries)
//		float MaxZ;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boundaries)
//		float MinZ;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Boundaries)
//		float boundaryFix;
//	//The Actor Class used in the swarm
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmActor)
//		UClass *ActorClass;
//	//Swarm Actor
//	AswarmActor* SwAct;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmActor)
//		UAnimationAsset* animationAsset;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmActor)
//		UAnimBlueprintGeneratedClass* anim;
//	USkeletalMeshComponent* FoundComp;
//		//The Skeletal Mesh applied to the swarmObject
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmActor)
//		UStaticMesh* A_Sm;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmActor)
//		USkeletalMesh* A_Skm;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmActor)
//		bool skeletalYN ;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
//		FVector sep;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
//		FVector ali;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
//		FVector coh;
//	FVector* ali2;
//	//////////////////////////////
//	//////////////Swarm Functions
//	//////////////////////////////
//
//	//Makes Swarm
//	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
//		void CreateSwarm();
//	//Swarm Cohesion
//	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
//		FVector cohesion(AswarmActor* b);
//	//Swarm Separation
//	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
//		FVector separation(AswarmActor* b);
//	//Swarm Alignment
//	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
//		FVector alignment(AswarmActor* b);
//	FVector alignmentTwo(FVector b);
//
//	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
//		FVector Boundaries(AswarmActor* b);
//	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
//		float Scatter(AswarmActor* b);
//	////////////////////////////
//	////bools to pick functions
//	/////////////////////////////
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmFunctions)
//		bool CohesionOn;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmFunctions)
//		bool AlignmentOn;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmFunctions)
//		bool SeparationOn;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmFunctions)
//		bool BoundariesOn;
//
//	////////////////////////////////////////////
//	//////////////testing class stuff
//	////////////////////////////////////////////
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmFunctions)
//		UClass* theClass;
//	////UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmFunctions)
//		TMap < AActor*, FVector* > theMap;
//	FVector* velocityTest;
//
//private:
//	//Apply Basic Swarm Intelligence
//	UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
//		 void ApplyBasicSwarming(float tick);
//	
//	
//};
