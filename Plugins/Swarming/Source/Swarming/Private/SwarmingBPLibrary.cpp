#include "SwarmingPrivatePCH.h"
#include "SwarmingBPLibrary.h"

USwarmingBPLibrary::USwarmingBPLibrary(const FObjectInitializer& ObjectInitializer) 
: Super(ObjectInitializer)
{

}

float USwarmingBPLibrary::SwarmingSampleFunction(float Param)
{
	return -1;
}

FVector USwarmingBPLibrary::Separation(AActor* act, AActor* agent)
{
	return act->GetActorLocation() - agent->GetActorLocation();
}

FVector USwarmingBPLibrary::Alignment(AActor* act, AActor* agent)
{
	return agent->GetVelocity();
}
FVector USwarmingBPLibrary::Cohesion(AActor* act, AActor* agent)
{
	return agent->GetActorLocation();
}
void USwarmingBPLibrary::ApplyBasicSwarming(float EventTick, TArray<AActor*> swarmArray, bool canFly, 
	TArray<FVector>& velocityArray,	float separationWeight, float alignmentWeight, float cohesionWeight,
	bool separationOn, bool alignmentOn, bool cohesionOn)
{
	//TArray<FVector*>velocityArray;
	if (velocityArray.Num() < swarmArray.Num())
	{
		for (int i = 0; i < swarmArray.Num(); i++)
		{
			FVector* velocity = new FVector();
			(*velocity) = swarmArray[i]->GetVelocity();
			velocityArray.Add((*velocity));
		}
	}
	for (int i = 0; i < swarmArray.Num(); i++)
	{
		
		FVector alignmentV = FVector().ZeroVector;
		FVector cohesionV = FVector().ZeroVector;
		FVector separationV = FVector().ZeroVector;
		FVector boundV = FVector().ZeroVector;
		FVector traceV = FVector().ZeroVector;
		FVector totalV = FVector().ZeroVector;
		

		float dist;
		float speed = 1;
		int32 agents = 0;
		for (int j = 0; j < swarmArray.Num(); j++)
		{
			if (swarmArray[i] != swarmArray[j])
			{
				dist = GetDistance(swarmArray[i], swarmArray[j]);
				if (dist <1000)
				{
					if (separationOn)
					separationV += separationV - (Separation(swarmArray[i], swarmArray[j])/100);
					if (alignmentOn)
					alignmentV += alignmentV + Alignment(swarmArray[i], swarmArray[j])/100;
					if (cohesionOn)
					cohesionV += cohesionV + Cohesion(swarmArray[i], swarmArray[j])/100;
				}
			}
		}
		cohesionV = (cohesionV - swarmArray[i]->GetActorLocation())/swarmArray.Num()-1;
		alignmentV = alignmentV / swarmArray.Num() - 1;
		totalV = (separationV*separationWeight) + (alignmentV*alignmentWeight)
			+ (cohesionV*cohesionWeight) + swarmArray[i]->GetVelocity();

		if (!canFly)
		{
			totalV.Z = 0;
		}
		velocityArray[i] = (velocityArray[i] + totalV) * speed;

		swarmArray[i]->SetActorLocation(swarmArray[i]->GetActorLocation() + velocityArray[i] * EventTick);
		
		velocityArray[i] = velocityArray[i].GetClampedToSize(0, 360);
		swarmArray[i]->SetActorRotation(velocityArray[i].Rotation());
	}
}
float USwarmingBPLibrary::GetDistance(AActor* act, AActor* agent)
{
	return FVector::Dist(act->GetActorLocation(), agent->GetActorLocation());
}
TArray<AActor*> USwarmingBPLibrary::CreateSwarm(UClass* agentClass, bool canFly, int32 swarmSize, float minMaxX,
	float minMaxY, float maxZ)
{
	TArray<AActor*> swarmArray;
	TObjectIterator<ACameraActor> It;
	AActor* SwAct;
	UWorld* world = It->GetWorld();

	if (world)
	{
		
		FRotator rot = FRotator().ZeroRotator;
		for (int i = 0; i < swarmSize; ++i)
		{
			//new random location for each object
			float x = FMath().RandRange(-minMaxX, minMaxX);
			float y = FMath().RandRange(-minMaxY, minMaxY);
			float z;
			if (canFly)
			{
				z = FMath().RandRange(100, maxZ);
			}
			else
			{
				z = 100;// It->GetActorLocation().Z;
			}

			FActorSpawnParameters SpawnParams;


			//spawn actor
			SwAct = world->SpawnActor<AActor>(agentClass, FVector(x, y, z), rot, SpawnParams);
			//adds actor to swarm array
			swarmArray.Push(SwAct);

		}
	}
	return swarmArray;
}