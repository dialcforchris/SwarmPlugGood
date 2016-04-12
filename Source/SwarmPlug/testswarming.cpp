// Fill out your copyright notice in the Description page of Project Settings.

#include "SwarmPlug.h"
#include "testswarming.h"



Utestswarming::Utestswarming()//(const FObjectInitializer& ObjectInitializer)
	//: Super(ObjectInitializer)
{

}

float Utestswarming::SwarmingSampleFunction(float Param)
{
	return -1;
}

FVector Utestswarming::Separation(AActor* act, AActor* agent)
{
	FVector sep = FVector::ZeroVector;
	sep = sep - (agent->GetActorLocation() - act->GetActorLocation());
	return sep;
}

FVector Utestswarming::Alignment(AActor* act, AActor* agent)
{
	FVector ali = FVector::ZeroVector;
	ali = ali + agent->GetVelocity();
	return ((ali - act->GetVelocity()) / 100).GetClampedToMaxSize(100);
}

FVector Utestswarming::Cohesion(AActor* act, AActor* agent)
{
	FVector coh = FVector::ZeroVector;
	coh = (coh + agent->GetActorLocation());
	

	return coh;
}

void Utestswarming::ApplyBasicSwarming(float EventTick, TArray<AActor*> swarmArray, TArray<FVector> velocityArray,bool canFly,
	TArray<AActor*>&outActors, TArray<FVector>&outVelocities,float separationWeight, float alignmentWeight, float cohesionWeight,
	bool separationOn, bool alignmentOn, bool cohesionOn,float maxAgentDistance,float speed)
{
	TArray<FVector> velArray = velocityArray;
	TArray<AActor*>acts = swarmArray;

	

	

	//TArray<FVector>vel = velocityArray;
	for (int i = 0; i < acts.Num(); i++)
	{

		FVector alignmentV = FVector().ZeroVector;
		FVector cohesionV = FVector().ZeroVector;
		FVector separationV = FVector().ZeroVector;
		FVector traceV = FVector().ZeroVector;
		FVector totalV = FVector().ZeroVector;
		velocityArray[i] = swarmArray[i]->GetVelocity();

		float dist;
		
		int32 agents = 0;

		for (int j = 0; j < swarmArray.Num(); j++)
		{
			if (i != j)
			{
				dist = GetDistance(swarmArray[i], swarmArray[j]);
				if (dist <maxAgentDistance)
				{
					if (separationOn)
						separationV = separationV + Separation(swarmArray[i], swarmArray[j]).GetClampedToSize(-300, 300);
					if (alignmentOn)
						alignmentV += Alignment(swarmArray[i],swarmArray[j]).GetClampedToSize(-100,100);
						//alignmentV = alignmentV + Alignment(swarmArray[i], swarmArray[j]);// / 100);// .GetClampedToSize(-100, 100);
					if (cohesionOn)
						cohesionV +=  Cohesion(swarmArray[i], swarmArray[j]).GetClampedToSize(-100, 100);
					agents++;
				}
				
			}
		}
		if (agents <=2)
		{
			maxAgentDistance += 100;
		}

			traceV = Avoidance(ConeTrace(swarmArray[i]));
			cohesionV = ((cohesionV / swarmArray.Num() - 1)* cohesionWeight);// .GetClampedToSize(-200, 200);
			//cohesionV = cohesionV * cohesionWeight;// .GetClampedToSize(-100, 100);
			alignmentV = ((alignmentV / swarmArray.Num() - 1)*alignmentWeight);// .GetClampedToSize(-200, 200);
			//alignmentV = alignmentV * alignmentWeight;// .GetClampedToSize(-100, 100);
			separationV = separationV*separationWeight;// .GetClampedToSize(-300, 300);
			totalV = traceV + separationV + cohesionV + alignmentV + acts[i]->GetVelocity();
		
		
		if (!canFly)
		{
			totalV.Z = 0;
		}
		velocityArray[i] =  (velocityArray[i] + totalV) * speed;

		
		outActors = swarmArray;
		outVelocities = velocityArray;
	}
}
void Utestswarming::SetLocation(TArray<FVector>velArray, TArray<AActor*>actors,float tick)
{
	for (int i = 0; i < actors.Num(); i++)
	{
		actors[i]->SetActorLocation(actors[i]->GetActorLocation() + velArray[i] * tick);
		velArray[i] = velArray[i].GetClampedToSize(0, 360);
		actors[i]->SetActorRotation(velArray[i].Rotation());
		velArray[i] = actors[i]->GetVelocity();
	}
}
float Utestswarming::GetDistance(AActor* act, AActor* agent)
{
	return FVector::Dist(act->GetActorLocation(), agent->GetActorLocation());
}

void Utestswarming::CreateSwarm(UClass* agentClass, bool canFly, TArray<AActor*>& swarmArray, 
	TArray<FVector>& velocityArray, int32 swarmSize, float minMaxX,	float minMaxY, float maxZ)
{
	
	FVector velocity; 
	TObjectIterator<ACameraActor> It;
	AActor* SwAct;
	UWorld* world = It->GetWorld();

	if (world)
	{

		FRotator rot = FRotator().ZeroRotator;
		for (int i = 0; i < swarmSize; i++)
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
			SwAct->SetTickGroup(ETickingGroup::TG_PostPhysics);
			velocity =  FVector::ZeroVector;
			velocityArray.Push(velocity);
			//adds actor to swarm array
			swarmArray.Push(SwAct);

		}
	}
}
FHitResult Utestswarming::ConeTrace(AActor* act, float radius, float traceLength, bool renderConeTrace, bool canFly)
{
	FHitResult hit;



	FVector pos;
	FRotator rot;
	act->GetActorEyesViewPoint(pos, rot);

	ECollisionChannel trace = ECollisionChannel::ECC_WorldDynamic;
	const FName TraceTag("Trace");
	FCollisionQueryParams params;
	if (renderConeTrace)
	{

		act->GetWorld()->DebugDrawTraceTag = TraceTag;
		params.TraceTag = TraceTag;
	}

	params.AddIgnoredActor(act);

	radius = 0;
	pos.Z -= 10;
	if (!canFly)
	{
		rot.Pitch = 0;
		rot.Roll = 0;
		radius = 0.5;
	}
	else
	{
		radius = 1;
	}
	FVector randomCone = FMath::VRandCone(rot.Vector(), radius);
	FVector end = pos + (randomCone * traceLength);

	act->GetWorld()->LineTraceSingleByChannel(hit, pos, end, trace, params);



	return hit;
}

FVector Utestswarming::Avoidance(FHitResult hit)
{
	return -(hit.Location/100);
}