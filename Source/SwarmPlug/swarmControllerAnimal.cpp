// Fill out your copyright notice in the Description page of Project Settings.

#include "SwarmPlug.h"
#include "swarmControllerAnimal.h"

AswarmControllerAnimal::AswarmControllerAnimal()
{
	PrimaryActorTick.bCanEverTick = true;
	behave = new Behaviours;
	canFly = false;

	//set variables to sensible amounts
	playerDistance = 200;
	speed = 0.5;
	scaleSep = 2;
	playerAvoidance = 10;
	maxDist = 700;
}

void AswarmControllerAnimal::BeginPlay()
{
	Super::BeginPlay();
	player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	box = NULL;
	
}
void AswarmControllerAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	targetLocation = target->GetActorLocation();
	arraySize = swarmArray.Num();

}
void AswarmControllerAnimal::StopToEat(float tick, AActor* food, AswarmActor* act)
{
	/*act->velocity = act->velocity + MoveTo(food->GetActorLocation(), act);
	timer += tick;
	if (timer >= 10)
	{
		act->behave = Behaviours::IDLE;
	}*/
}

FVector AswarmControllerAnimal::RunFrom(ACharacter* AC,AswarmActor* act)
{
	
	FVector run = FVector().ZeroVector;

		if (FVector().Dist(act->GetActorLocation(), AC->GetActorLocation()) < playerDistance)
		{
			run = ((act->GetActorLocation() - AC->GetActorLocation())) * playerAvoidance;

		}
		
		return run + AC->GetVelocity()/100;
}
FVector AswarmControllerAnimal::MoveTo(FVector target, AswarmActor* act)
{
	
		FVector move = FVector().ZeroVector;

		if (FVector().Dist(act->GetActorLocation(), target)>200)
		{
			FMath::LerpStable(act->GetActorLocation(), target, 0.1);

		}
		else
		{
			act->behave = Behaviours::IDLE;
		}
		
	
	return move;
}


void AswarmControllerAnimal::StateManager(AswarmActor* act)
{
	
	{

	}

}
void AswarmControllerAnimal::AnimalApply(float tick)
{
	FVector alignmentV = FVector().ZeroVector;
	FVector cohesionV = FVector().ZeroVector;
	FVector separationV = FVector().ZeroVector;
	FVector boundV = FVector().ZeroVector;
	FVector moveToV = FVector().ZeroVector;
	FVector runV = FVector().ZeroVector;
	FVector idleV = FVector().ZeroVector;
	FVector totalV = FVector().ZeroVector;
	for (int i = 0; i < swarmArray.Num(); i++)
	{
		swarmArray[i]->behave = Behaviours::IDLE;
		if (swarmArray[i]->behave == Behaviours::RUN)
		{
			runV = (RunFrom(player, swarmArray[i]));
			separationV = separation(swarmArray[i]);
		}
		if (swarmArray[i]->behave == Behaviours::IDLE)
		{
			float boxDist = FVector().Dist(swarmArray[i]->GetActorLocation(), box.GetCenter());
			if (box == NULL)
			{
				localpoint = LocalPoint(swarmArray[i]);
			}
			
			if (boxDist <= 20)
			{
				idleV = swarmArray[i]->GetActorLocation().GetClampedToSize(5, 20);
			}
			else
			{
				idleV = localpoint / 100;// *boxDist;
			}
		}
			
			//moveToV = MoveTo(targetLocation, swarmArray[i])*tick;
		
		if (swarmArray[i]->behave == Behaviours::MOVETOTARGET)
		{
			if (BoundariesOn)
				boundV = Boundaries(swarmArray[i]);
			if (SeparationOn)
				separationV = separation(swarmArray[i]);
			if (CohesionOn)
				cohesionV = cohesion(swarmArray[i]) / 100;
			
		}
		
		//scale the returned values
		separationV = (separationV *scaleSep);// .ClampSize(-200, 200);
		cohesionV = (cohesionV *scaleCoh).GetClampedToSize(-20, 20);
		alignmentV = (alignmentV * scaleAli).GetClampedToSize(-200, 200);
		
		float appliedSpeed = speed * tick;
		totalV = (separationV + cohesionV + alignmentV + boundV + moveToV + runV + idleV);
		if (!canFly)
		{
			totalV.Z = 0;
		}
		swarmArray[i]->velocity = (swarmArray[i]->velocity + totalV)*speed;
	}

}
FVector AswarmControllerAnimal::LocalPoint(AActor* act)
{
	
	FVector boxDimensions = FVector(50, 50, 50);
	box = FBox(GetActorLocation() - (boxDimensions),GetActorLocation() + boxDimensions);
	FVector idlepoint = FMath::RandPointInBox(box);
	
	return (idlepoint -act->GetActorLocation())*FVector().Dist(idlepoint,act->GetActorLocation())/100;
}


































void AswarmControllerAnimal::ApplyAnimalFunctions(float tick)
{
	for (int i = 0; i < swarmArray.Num(); i++)
	{
		randomNumber = FMath().RandRange(0, 10);
		if (randomNumber >= 3)
		{

			swarmArray[i]->behave = Behaviours::MOVETOTARGET;

		}
	}

}
