// Fill out your copyright notice in the Description page of Project Settings.

#include "SwarmPlug.h"
#include "swarmControllerAnimal.h"

AswarmControllerAnimal::AswarmControllerAnimal()
{
	PrimaryActorTick.bCanEverTick = true;
	behave = new Behaviours;
	canFly = false;

	//set variables to sensible amounts
	playerDistance = 100;
	traceLength = 200;
	speed = 0.5;
	scaleSep = 2;
	playerAvoidance = 10;
	maxDist = 100;
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

		if (FVector().Dist(act->GetActorLocation(), target)>300)
		{
			move = (target)*0.1;

		}
		else
		{
			//act->behave = Behaviours::IDLE;
		}
		
	
	return move;
}


Behaviours AswarmControllerAnimal::StateManager(AswarmActor* act,float tick)
{
	int32 random = FMath::RandRange(0, 100);
	switch (act->behave)
	{
	case MOVETOTARGET:
	{
		if (FVector::Dist(act->GetActorLocation(), player->GetActorLocation()) < playerDistance)
		{
			return Behaviours::RUN;
		}
		else if (random > 90)
		{
			return Behaviours::IDLE;
		}
		else if (random < 10)
		{
			return Behaviours::FOLLOW;
		}
		break;
	}
	case RUN:
	{
		if (FVector::Dist(act->GetActorLocation(), player->GetActorLocation())>200)
		{
			if (random < 5)
			{
				return Behaviours::IDLE;
			}
			else if (random > 95)
			{
				return Behaviours::FOLLOW;
			}
			else
			{
				return Behaviours::MOVETOTARGET;
			}
			break;
		}
	}
	case FOLLOW:
	{
		timer += tick;
		if (timer >= 2)
		{
			timer = 0;
			return Behaviours::MOVETOTARGET;
		}
		break;
	}
	case IDLE:
	{
		swtch = !swtch;
		timer += tick;
		if (timer >= 2)
		{
			if (swtch)
			{
				return Behaviours::MOVETOTARGET;
			}
			else
			{
				return Behaviours::FOLLOW;
			}
		}
		break;
	}
	}
	
	return Behaviours::MOVETOTARGET;



}
void AswarmControllerAnimal::AnimalApply(float tick)
{
	
	
	
	for (int i = 0; i < swarmArray.Num(); i++)
	{
		int32 agents = 0;

		FVector alignmentV = FVector().ZeroVector;
		FVector cohesionV = FVector().ZeroVector;
		FVector separationV = FVector().ZeroVector;
		FVector boundV = FVector().ZeroVector;
		FVector moveToV = FVector().ZeroVector;
		FVector runV = FVector().ZeroVector;
		FVector idleV = FVector().ZeroVector;
		FVector totalV = FVector().ZeroVector;
		FVector lineV = FVector::ZeroVector;
		swarmArray[i]->behave =  StateManager(swarmArray[i], tick);
		//lineV = Avoidance(swarmArray[i]);
		for (int j = 0; j < swarmArray.Num(); j++)
		{
			float dist = 0;
			
			if (swarmArray[i] != swarmArray[j])
			{
				dist = GetDistance(swarmArray[i], swarmArray[j]);

				if (swarmArray[i]->behave == Behaviours::RUN)
				{
					runV = (RunFrom(player, swarmArray[i]));
					if (dist < maxDist)
					{
						separationV = separation(swarmArray[i], dist, swarmArray[j]);
						agents++;
					}
				}

				else if (swarmArray[i]->behave == Behaviours::IDLE)
				{
					float boxDist;
					if (box == NULL)
					{
						localpoint = LocalPoint(swarmArray[i]);
						boxDist = FVector().Dist(swarmArray[i]->GetActorLocation(), box.GetCenter());

					}

					if (boxDist <= 20)
					{
						idleV = swarmArray[i]->GetActorLocation().GetClampedToSize(0, 1);
					}
					else
					{
						idleV = localpoint - swarmArray[i]->GetActorLocation() / 70;
					}
					if (dist < maxDist)
					{
						alignmentV = alignment(swarmArray[i], dist, swarmArray[j]);
						agents++;
					}


				}
				else if (swarmArray[i]->behave == Behaviours::FOLLOW)
				{
					moveToV = MoveTo(player->GetActorLocation(), swarmArray[i])/100;
					if (dist < maxDist)
					{
						separationV = separation(swarmArray[i], dist, swarmArray[j]);
						agents++;
					}

				}


				else if (swarmArray[i]->behave == Behaviours::MOVETOTARGET)
				{
					if (dist < maxDist)
					{

						if (SeparationOn)
							separationV += separation(swarmArray[i], dist, swarmArray[j]);
						if (CohesionOn)
							cohesionV += cohesion(swarmArray[i], dist, swarmArray[j]) / 100;
						alignmentV += alignment(swarmArray[i], dist, swarmArray[j]);
						agents++;
					}

				}
			}
		}
		//scale the returned values
		lineV = Collision(ConeTracer(swarmArray[i], ECollisionChannel::ECC_Camera));// swarmArray[i]->LineTracer();
		separationV = (separationV *scaleSep);
		cohesionV = ((cohesionV/agents) *scaleCoh).GetClampedToSize(-20, 20);
		alignmentV = ((alignmentV/agents) * scaleAli).GetClampedToSize(-200, 200);
		boundV = Boundaries(swarmArray[i]);
		//lineV = lineV.GetClampedToSize(-20, 20);
		//float appliedSpeed = speed * tick;
		totalV =  (separationV + cohesionV + alignmentV + moveToV + runV + idleV + lineV);
		if (!canFly)
		{
			totalV.Z = 0;
		}
		swarmArray[i]->velocity = (swarmArray[i]->velocity + totalV )*speed;
		if (swarmArray[i]->behave != Behaviours::RUN)
		{
			if (swarmArray[i]->velocity.Size() > 200)
			{
				swarmArray[i]->velocity -= swarmArray[i]->velocity / 100;
			}
		}
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
