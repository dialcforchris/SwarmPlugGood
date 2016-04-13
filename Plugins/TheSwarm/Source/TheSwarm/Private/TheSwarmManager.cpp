#pragma once
#include "TheSwarmPrivatePCH.h"

ATheSwarmManager::ATheSwarmManager(const class FObjectInitializer& PCIP) :Super(PCIP)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void ATheSwarmManager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATheSwarmManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATheSwarmManager::CreateSwarm()
{
	UWorld* const world = GetWorld();
	if (world)
	{
		//gets random positions withing range of manager
		int MinMaxX = 1000 + this->GetActorLocation().X;
		int MinMaxY = 1000 + this->GetActorLocation().Y;
		int MinMaxZ = 800 + this->GetActorLocation().Z;
		FRotator rot = FRotator().ZeroRotator;
		for (int i = 0; i < swarmSize; ++i)
		{
			//new random location for each object
			float x = FMath().RandRange(-MinMaxX, MinMaxX);
			float y = FMath().RandRange(-MinMaxY, MinMaxY);
			float z;
			if (canFly)
			{
				z = FMath().RandRange(0, MinMaxZ);
			}
			else
			{
				z = this->GetActorLocation().Z;
			}

			FActorSpawnParameters SpawnParams;


			//spawn actor
			SwAct = GetWorld()->SpawnActor<ATheSwarmActor>(TheSwarmActorClass, FVector(x, y, z), rot, SpawnParams);
			SwAct->swarmClass = AgentClass;
			SwAct->SpawnActors(AgentClass);

			//adds actor to swarm array
			swarmArray.Push(SwAct);

		}
	}
}

void ATheSwarmManager::ApplyBasicSwarming(float tick)
{

	for (int i = 0; i < swarmArray.Num(); i++)
	{


		FVector alignmentV = FVector().ZeroVector;
		FVector cohesionV = FVector().ZeroVector;
		FVector separationV = FVector().ZeroVector;
		FVector boundV = FVector().ZeroVector;
		FVector traceV = FVector().ZeroVector;
		totalV = FVector().ZeroVector;
		FVector Velocity = FVector::ZeroVector;
		float dist;
		agents = 0;

		for (int j = 0; j < swarmArray.Num(); j++)
		{
			dist = 0;
			if (swarmArray[i] != swarmArray[j])
			{
				dist = GetDistance(swarmArray[i], swarmArray[j]);

				{
					//get results
					
						separationV += separation(swarmArray[i], dist, swarmArray[j]).GetClampedToSize(-300, 300);
						alignmentV += alignment(swarmArray[i], dist, swarmArray[j]).GetClampedToSize(-100, 100);
						cohesionV += cohesion(swarmArray[i], dist, swarmArray[j]).GetClampedToSize(-100, 100);

				}

			}
		}
		if (BoundariesOn)
			boundV = Boundaries(swarmArray[i]);
		traceV = Collision(ConeTracer(swarmArray[i], ECollisionChannel::ECC_Camera));
		if (!SeparationOn)
		{
			scaleSep = 0;
		}
		if (!CohesionOn)
		{
			scaleCoh = 0;
		}
		if (!AlignmentOn)
		{
			scaleAli = 0;
		}
		//scale the returned values
		separationV = separationV *scaleSep;
		cohesionV = ((cohesionV / swarmArray.Num() - 1) *scaleCoh);
		alignmentV = ((alignmentV / swarmArray.Num() - 1) * scaleAli);
		totalV = traceV + separationV + boundV + cohesionV + alignmentV + swarmArray[i]->GetVelocity();
		if (!canFly)
		{
			totalV.Z = 0;
		}
		if (totalV.Z <= 0)
		{
			totalV.Z += 10;
		}
		swarmArray[i]->velocity = (swarmArray[i]->velocity + totalV) * speed;
		if (swarmArray[i]->velocity.Size() > 200)
		{
			swarmArray[i]->velocity -= swarmArray[i]->velocity / 100;
		}


	}
}
FHitResult ATheSwarmManager::ConeTracer(ATheSwarmActor* act, ECollisionChannel channel)
{
	FHitResult hit;
	if (act->actor)
	{

		FVector pos;
		FRotator rot;
		act->actor->GetActorEyesViewPoint(pos, rot);

		ECollisionChannel trace = channel;
		const FName TraceTag("Trace");
		FCollisionQueryParams params;
		if (renderConeTrace)
		{

			GetWorld()->DebugDrawTraceTag = TraceTag;
			params.TraceTag = TraceTag;
		}

		params.AddIgnoredActor(act);
		params.AddIgnoredActor(act->actor);
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

		GetWorld()->LineTraceSingleByChannel(hit, pos, end, trace, params);

	}

	return hit;
}
void ATheSwarmManager::AddRemoveAgents()
{
	int MinMaxX = 1000 + this->GetActorLocation().X;
	int MinMaxY = 1000 + this->GetActorLocation().Y;
	int MinMaxZ = 800 + this->GetActorLocation().Z;
	FRotator rot = FRotator().ZeroRotator;

	if (swarmArray.Num() < swarmSize)
	{
		float x = FMath().RandRange(-MinMaxX, MinMaxX);
		float y = FMath().RandRange(-MinMaxY, MinMaxY);
		float z;
		if (canFly)
		{
			z = FMath().RandRange(0, MinMaxZ);
		}
		else
		{
			z = this->GetActorLocation().Z;
		}

		FActorSpawnParameters SpawnParams;


		//spawn actor
		SwAct = GetWorld()->SpawnActor<ATheSwarmActor>(TheSwarmActorClass, FVector(x, y, z), rot, SpawnParams);
		SwAct->swarmClass = AgentClass;
		SwAct->SpawnActors(AgentClass);

		//adds actor to swarm array
		swarmArray.Push(SwAct);
	}
	if (swarmArray.Num() > swarmSize)
	{
		swarmArray.Pop(true);
		//Destroy(swarmArray[swarmArray.Num()]);
	}
}
FVector ATheSwarmManager::Collision(FHitResult hit)
{
	return -(hit.Location / 20);
}

float ATheSwarmManager::GetDistance(AActor* a, AActor* b)
{
	float distance = 0;

	distance = FVector::Dist(a->GetActorLocation(), b->GetActorLocation());
	return distance;

}
FVector ATheSwarmManager::Boundaries(ATheSwarmActor* b)
{
	Bound = FVector().ZeroVector;
	if (b->GetActorLocation().X < MinX)
	{
		Bound.X = boundaryFix;
	}
	if (b->GetActorLocation().X > MaxX)
	{
		Bound.X = -boundaryFix;
	}
	if (b->GetActorLocation().Y < MinY)
	{
		Bound.Y = boundaryFix;
	}
	if (b->GetActorLocation().Y > MaxY)
	{
		Bound.Y = -boundaryFix;
	}
	if (b->GetActorLocation().Z < MinZ)
	{
		Bound.Z = boundaryFix;
	}
	if (b->GetActorLocation().Z > MaxZ)
	{
		Bound.Z = -boundaryFix;
	}
	return Bound;
}

FVector ATheSwarmManager::alignment(ATheSwarmActor* b, float dist, ATheSwarmActor* a)
{
	ali = FVector::ZeroVector;
	
			if (dist < maxDist)
			{
				ali = ali + a->GetVelocity();

			}

	return ((ali - b->GetVelocity()) / 100).GetClampedToMaxSize(100);
}

FVector ATheSwarmManager::separation(ATheSwarmActor* b, float dist, ATheSwarmActor* a)
{
	sep = FVector().ZeroVector;
	
				if (dist < maxDist)
				{

					sep = sep - (a->GetActorLocation() - b->GetActorLocation());// minus;
				}
	return sep;
}

FVector ATheSwarmManager::cohesion(ATheSwarmActor* b, float dist, ATheSwarmActor* a)
{

	coh = FVector().ZeroVector;

	if (dist < maxDist)
		{
			coh = coh + a->GetActorLocation();
		}
		
	coh = coh - b->GetActorLocation();
	return coh;
}
