#pragma once

#include "Engine.h"
#include "TheSwarmActor.h"
#include "TheSwarmManager.generated.h"

UCLASS()
class THESWARM_API ATheSwarmManager : public AActor
{

	GENERATED_UCLASS_BODY()

public:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;
	
		// Called every frame
		virtual void Tick(float DeltaSeconds) override;
		//swarm array
		UPROPERTY(BlueprintReadOnly)
		TArray <ATheSwarmActor*> swarmArray;
		//the size of the swarm (should always be greater than 2)
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			int32 swarmSize = 10;
		//max agent distance
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
		//The TheSwarmActor Class needed to spawn the swarm (should always be inherited from TheSwarmActor)
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmActor)
			TSubclassOf<ATheSwarmActor> TheSwarmActorClass;
		//The class for the swarm
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmActor)
			UClass* AgentClass;
		//Swarm Actor
		ATheSwarmActor* SwAct;
		UPROPERTY(BlueprintReadWrite)
			FVector sep;
		UPROPERTY(BlueprintReadWrite)
			FVector ali;
		UPROPERTY(BlueprintReadWrite)
			FVector coh;
		UPROPERTY(BlueprintReadWrite)
			FVector Bound;
		UPROPERTY(BlueprintReadWrite)
			FVector totalV;

			//////////////////////////////
			//////////////Swarm Functions
			//////////////////////////////
		
		//Makes Swarm
		UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
			void CreateSwarm();
		UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
			void AddRemoveAgents();
		////
		//Cone trace elements
		////
		UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
			FHitResult ConeTracer(ATheSwarmActor* act, ECollisionChannel channel);
		
			FHitResult hit;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmFunctions)
			bool renderConeTrace = true;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmFunctions)
			float traceLength = 200;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SwarmFunctions)
			float radius;
		UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
			FVector Collision(FHitResult hit);
		
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
		//Swarm Cohesion
		UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
			FVector cohesion(ATheSwarmActor* b, float dist, ATheSwarmActor* a);
		//Swarm Separation
		UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
			FVector separation(ATheSwarmActor* b, float dist, ATheSwarmActor* a);
		//Swarm Alignment
		UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
			FVector alignment(ATheSwarmActor* b, float dist, ATheSwarmActor* a);
		UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
			FVector Boundaries(ATheSwarmActor* b);
		//Apply Basic Swarm Intelligence
		UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
			void ApplyBasicSwarming(float tick);
		UFUNCTION(BlueprintCallable, Category = SwarmFunctions)
			float GetDistance(AActor* a, AActor* b);
			int32 agents;
};



