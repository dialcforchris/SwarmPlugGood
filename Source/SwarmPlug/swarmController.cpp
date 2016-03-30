// Fill out your copyright notice in the Description page of Project Settings.

#include "SwarmPlug.h"
#include "swarmController.h"



// Sets default values
AswarmController::AswarmController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AswarmController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AswarmController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


void AswarmController::CreateSwarm()
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
			SwAct = GetWorld()->SpawnActor<AswarmActor>(ActorClass, FVector(x, y, z), rot, SpawnParams);


			//adds actor to swarm array
			swarmArray.Push(SwAct);

		}
	}
}

void AswarmController::ApplyBasicSwarming(float tick)
{

	for (int i = 0; i < swarmArray.Num(); i++)
	{
		N = 0;
		FVector alignmentV = FVector().ZeroVector;
		FVector cohesionV = FVector().ZeroVector;
		FVector separationV = FVector().ZeroVector;
		FVector boundV = FVector().ZeroVector;
		totalV = FVector().ZeroVector;
		//GetDist(swarmArray[i]);
		//get results
		if (SeparationOn)
			separationV = separation(swarmArray[i]).GetClampedToSize(-300, 300);
		if (AlignmentOn)
			alignmentV = alignment(swarmArray[i]).GetClampedToSize(-100,100);
		if (CohesionOn)
			cohesionV = cohesion(swarmArray[i]).GetClampedToSize(-100,100);
		if (BoundariesOn)
			boundV = Boundaries(swarmArray[i]);

		//scale the returned values
		separationV = separationV *scaleSep;
		cohesionV = cohesionV *scaleCoh;
		alignmentV = alignmentV * scaleAli;
		float appliedSpeed = speed * tick;
		totalV = separationV + cohesionV + alignmentV + boundV;
		if (!canFly)
		{
			totalV.Z = 0;
		}
		swarmArray[i]->velocity = (swarmArray[i]->velocity + totalV)*appliedSpeed;
		

	}
}
FVector AswarmController::Boundaries(AswarmActor* b)
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

	/*if (b->GetActorLocation().X < MinX)
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
	Bound = ((b->GetActorLocation() - Bound));
	return Bound;*/
}
FVector AswarmController::alignmentTwo(FVector b)
{
	FVector ali2 = FVector().ZeroVector;
	for (int i = 0; i < velArray.Num(); i++)
	{
		if (b != velArray[i])
		{
			ali2 = ali2 + velArray[i];
		}
	}
	return ali2 / velArray.Num() - 1;
}

FVector AswarmController::alignment(AswarmActor* b)
{

	for (int i = 0; i < swarmArray.Num(); i++)
	{
		if (b != swarmArray[i])
		{
			ali = ali + swarmArray[i]->GetVelocity();
		}
		ali = ali / swarmArray.Num() - 1;
	}
	return (ali - b->GetVelocity());
	
}

FVector AswarmController::separation(AswarmActor* b)
{
	sep = FVector().ZeroVector;
	for (int i = 0; i < swarmArray.Num(); i++)
	{
		if (b != swarmArray[i])
		{
			if (FVector().Dist(b->GetActorLocation(), swarmArray[i]->GetActorLocation()) < maxDist)
			{

				sep = sep - (swarmArray[i]->GetActorLocation() - b->GetActorLocation());// minus;
			}

		}
	}
	return sep;
}

FVector AswarmController::cohesion(AswarmActor* b)
{
	int dist = maxDist;
	coh = FVector().ZeroVector;
	for (int i = 0; i < swarmArray.Num(); i++)
	{
		if (b != swarmArray[i])
		{
			if (FVector().Dist(b->GetActorLocation(), swarmArray[i]->GetActorLocation()) < dist)
			{
				coh = coh + swarmArray[i]->GetActorLocation();
				N++;
			}
		}
		
		
		if (i == swarmArray.Num()-1 && N < 3)
		{
			i = 0;
			dist += 100;
		}
	}
	
	
	coh = coh - b->GetActorLocation();
	return coh;
}





























































//float AswarmController::Scatter(AswarmActor* b)
//{
//	//if (FVector().Dist(b->GetActorLocation(), player->GetComponentLocation()) < 50)
//	{
//		return -1;
//	}
//	//else
//	{
//		return 1;
//	}
//
//}
//
//void AswarmController::spawnfromclass()
//{
//	UWorld* const world = GetWorld();
//	if (world)
//	{
//		//gets random positions withing range of manager
//		int MinMaxX = 1000 + this->GetActorLocation().X;
//		int MinMaxY = 1000 + this->GetActorLocation().Y;
//		int MinMaxZ = 100 + this->GetActorLocation().Z;
//		FRotator rot = FRotator().ZeroRotator;
//		for (int i = 0; i < swarmSize; ++i)
//		{
//			//new random location for each object
//			float x = FMath().RandRange(-MinMaxX, MinMaxX);
//			float y = FMath().RandRange(-MinMaxY, MinMaxY);
//			float z = 0;
//			if (canFly)
//			{
//				z = FMath().RandRange(0, MinMaxZ);
//			}
//
//			FActorSpawnParameters SpawnParams;
//			UWorld* world = GetWorld();
//
//			if (world)
//			{//spawn actor
//				classAct = GetWorld()->SpawnActor<AActor>(aActorClass, FVector(x, y, z), rot, SpawnParams);
//				assignedVec = new FVector();
//				theMap.Add(classAct, assignedVec);
//
//			}
//		}
//
//	}
//}

void AswarmController::GetDist(AswarmActor* b)
{
	for (int i = 0; i < swarmArray.Num(); i++)
	{
		if (swarmArray[i] != b)
		{
			distArray.Add(swarmArray[i]);
		}
	}
	for (int j = 0; j < distArray.Num(); j++)
	{
		eachDist.Add(FVector().Dist(b->GetActorLocation(), distArray[j]->GetActorLocation()));
	}
//	SortByDist();
}
void AswarmController::SortByDist()
{
	for (int i = 0; i < eachDist.Num()-1; i++)
	{
		for (int j = 0; j < eachDist.Num()-1; j++)
		{
			if (eachDist[j] > eachDist[j + 1])
			{
				float tempD = eachDist[j];
				AswarmActor* tempA = distArray[j];
				eachDist[j] = eachDist[j + 1];
				distArray[j] = distArray[j + 1];
				eachDist[j + 1] = tempD;
				distArray[j + 1] = tempA;

			}
		}
	}
	
}
FVector AswarmController::ClAlignment(AswarmActor* b)
{
	
	for (int i = 0; i < nearestN; i++)
	{
	//if (b != swarmArray[i])
	{
	ali = ali + distArray[i]->velocity;
	}
	ali = ali / nearestN;
	}
	return (ali - b->velocity);
	// ali = FVector().ZeroVector;

	/*for (auto It = theMap.CreateIterator(); It; ++It)
	{
		if (It->Key != act)
		{
			ali = ali + (*It->Value);
		}
		ali = ali / theMap.Num() - 1;
	}
	return ali - (*theMap[act]);*/
}
FVector AswarmController::ClSeparation(AswarmActor* b)
{
	for (int i = 0; i < nearestN; i++)
 {
 //if (b != swarmArray[i])
 {
 //if (FVector().Dist(b->GetActorLocation(), swarmArray[i]->GetActorLocation()) < maxDist)
 {

 sep = sep - (distArray[i]->GetActorLocation() - b->GetActorLocation());// minus;
 }

 }
 }
 return sep / 100;
	// sep = FVector().ZeroVector;
	/*for (auto It = theMap.CreateIterator(); It; ++It)
	{
		if (It->Key != act)
		{
			if (FVector().Dist(act->GetActorLocation(), It->Key->GetActorLocation()) < maxDist)
			{

				sep = sep - (It->Key->GetActorLocation() - act->GetActorLocation());
			}
		}
	}
	return sep / 100;*/
}
FVector AswarmController::ClCohesion(AswarmActor* b)
{
	coh = FVector().ZeroVector;
	for (int i = 0; i < nearestN; i++)
	{
	//if (b != swarmArray[i])
	{
	coh = coh + distArray[i]->GetActorLocation();
	}
	}
	coh = coh / swarmArray.Num();
	return coh - b->GetActorLocation();
	
}
FVector AswarmController::ClBoundaries(AswarmActor* b)
{
	FVector Bound;// = FVector().ZeroVector;
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
//void AswarmController::ClApply(float tick)
//{
//	//				//get results
//	//			if (SeparationOn)
//	//				separationV = separation(swarmArray[i]);
//	//			if (AlignmentOn)
//	//				alignmentV = alignment(swarmArray[i]);
//	//			if (CohesionOn)
//	//				cohesionV = cohesion(swarmArray[i]) / 10;// *Scatter(swarmArray[i]) / 10;
//	//			if (BoundariesOn)
//	//				boundV = Boundaries(swarmArray[i]);
//
//	//			//scale the returned values
//	//				separationV = separationV *scaleSep;
//	//				cohesionV = cohesionV *scaleCoh;
//	//				alignmentV = alignmentV * scaleAli;
//	//				float appliedSpeed = speed * tick;
//	//				
//	//				swarmArray[i]->velocity = (swarmArray[i]->velocity + separationV + cohesionV + alignmentV + boundV)*speed;
//
//	FVector alignmentV = FVector().ZeroVector;
//	FVector cohesionV = FVector().ZeroVector;
//	FVector separationV = FVector().ZeroVector;
//	FVector boundV = FVector().ZeroVector;
//	FVector totalV = FVector().ZeroVector;
//
//	for (auto It = theMap.CreateIterator(); It; ++It)
//	{
//		if (SeparationOn)
//			separationV = ClSeparation(It->Key);
//		if (AlignmentOn)
//			alignmentV = ClAlignment(It->Key);
//		if (CohesionOn)
//			cohesionV = ClCohesion(It->Key) / 10000;
//		if (BoundariesOn)
//			boundV = ClBoundaries(It->Key);
//
//		//swarmArray[i]->velocity = (swarmArray[i]->velocity + separationV + cohesionV + alignmentV + boundV)*speed;
//		separationV = separationV *scaleSep;
//		cohesionV = cohesionV *scaleCoh * tick;
//		alignmentV = alignmentV * scaleAli;
//		(*It->Value) = ((*It->Value) + separationV + cohesionV + alignmentV + boundV) * speed;
//		float appliedSpeed = speed * tick;
//
//		//(*theMap[It->Key]) = totalV * speed;
//		//ClMovement(tick);
//		TArray<UMovementComponent*> Comps;
//		It->Key->GetComponents(Comps);
//		if (Comps.Num() > 0)
//		{
//			UMovementComponent* FoundComp = Comps[0];
//			FoundComp->Velocity = (*It->Value);//(*theMap[It->Key]);
//
//		}
//
//
//
//	}
//
//
//}
//
//void AswarmController::ClMovement(float tick)
//{
//	for (auto It = theMap.CreateIterator(); It; ++It)
//	{
//		/*TArray<UMovementComponent*> Comps;
//		It->Key->GetComponents(Comps);
//		if (Comps.Num() > 0)
//		{
//		UMovementComponent* FoundComp = Comps[0];
//		FoundComp->Velocity = (*It->Value);//(*theMap[It->Key]);
//
//		}*/
//		FVector pos = It->Key->GetActorLocation();
//		FVector velocity = (*It->Value);
//		velocity.X = (velocity.X + pos.X);// *tick;
//		velocity.Y = (velocity.Y + pos.Y);// *tick;
//		velocity.Z = (pos.Z);
//		FVector shrug = velocity;
//		It->Key->SetActorLocation(shrug + It->Key->GetActorLocation());// + FVector(velocity.X,velocity.Y,velocity.Z)*0.0001f);
//
//	}
//}

//
//// Fill out your copyright notice in the Description page of Project Settings.
//
//#include "SwarmPlug.h"
//#include "swarmController.h"
//
//
//// Sets default values
//AswarmController::AswarmController()
//{
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//	
//}
//
//// Called when the game starts or when spawned
//void AswarmController::BeginPlay()
//{
//	Super::BeginPlay();
//	CreateSwarm();
//}
//
//// Called every frame
//void AswarmController::Tick( float DeltaTime )
//{
//	Super::Tick( DeltaTime );
//	ApplyBasicSwarming(DeltaTime);
//}
//FVector AswarmController::alignment(AswarmActor* b)
//{
//	
//	for (int i = 0; i < swarmArray.Num(); i++)
//	{
//		if (b != swarmArray[i])
//		{
//			ali = ali + swarmArray[i]->velocity;
//		}
//		ali = ali / swarmArray.Num() - 1;
//	}
//	return (ali - b->velocity);
//}
//
//FVector AswarmController::separation(AswarmActor* b)
//{
//	
//	for (int i = 0; i < swarmArray.Num(); i++)
//	{
//		if (b != swarmArray[i])
//		{
//			if (FVector().Dist(b->GetActorLocation(), swarmArray[i]->GetActorLocation()) < maxDist)
//			{
//				/*FVector bV = b->GetActorLocation();
//				FVector sV = swarmArray[i]->GetActorLocation();
//				float xV = bV.X - sV.X;
//				float yV = bV.Y - sV.Y;
//				float zV = bV.Z - sV.Z;
//				FVector minus = FVector(xV, yV, zV);*/
//				sep = sep - (swarmArray[i]->GetActorLocation() - b->GetActorLocation());// minus;
//			}
//		
//		}
//	}
//	return sep/100;
//}
//
//FVector AswarmController::cohesion(AswarmActor* b)
//{
//	 coh = FVector().ZeroVector;;
//	for (int i = 0; i < swarmArray.Num(); i++)
//	{
//		if (b != swarmArray[i])
//		{
//			coh = coh + swarmArray[i]->GetActorLocation();
//		}
//	}
//	coh = coh / (swarmArray.Num() - 1);
//	return coh -b->GetActorLocation();
//}
//
//void AswarmController::CreateSwarm()
//{
//	UWorld* const world = GetWorld();
//	if (world)
//	{
//		//gets random positions withing range of manager
//		int MinMaxX = 1000 + this->GetActorLocation().X;
//		int MinMaxY = 1000 + this->GetActorLocation().Y;
//		int MinMaxZ = 100 + this->GetActorLocation().Z;
//		FRotator rot = FRotator().ZeroRotator;
//		for (int i = 0; i < swarmSize; ++i)
//		{
//			//new random location for each object
//			float x = FMath().RandRange(-MinMaxX, MinMaxX);
//			float y = FMath().RandRange(-MinMaxY, MinMaxY);
//			float z = FMath().RandRange(0, MinMaxZ);
//			FActorSpawnParameters SpawnParams;
//			
//			//spawn actor
//			SwAct = GetWorld()->SpawnActor<AswarmActor>(ActorClass, FVector(x, y, z), rot, SpawnParams);
//			
//		/*	TArray<UMeshComponent*> Comps;
//			SwAct->GetComponents(Comps);
//			if (Comps.Num() > 0)
//			{
//				UMeshComponent* FoundComp = Comps[0];
//				FoundComp = A_Mesh;
//				
//			}*/
//			//adds new static mesh
//			if (!skeletalYN)
//			{
//				TArray<UStaticMeshComponent*> Comps;
//				SwAct->GetComponents(Comps);
//				if (Comps.Num() > 0)
//				{
//					UStaticMeshComponent* FoundComp = Comps[0];
//					FoundComp->StaticMesh = A_Sm;
//					FoundComp->StaticMesh->BodySetup;
//					FoundComp->SetMaterial(0, A_Sm->GetMaterial(0));
//					
//				}
//				SwAct->skRotAdj = 180;
//			}
//			else
//			{
//				SwAct->skRotAdj = 90;
//				
//				TArray<USkeletalMeshComponent*> Comps;
//				SwAct->GetComponents(Comps);
//				if (Comps.Num() > 0)
//				{
//					//A_Skm->
//					FoundComp = Comps[0];
//					FoundComp->SetSkeletalMesh(A_Skm);
//					//FoundComp->AnimBlueprintGeneratedClass = anim;
//					FoundComp->SetAnimation(animationAsset);
//					FoundComp->BodySetup;
//					FoundComp->SetAnimationMode(EAnimationMode::AnimationBlueprint);
//					FoundComp->AnimBlueprintGeneratedClass = anim;
//					FoundComp->InitAnim(true);
//					
//						//FoundComp->AnimBlueprintGeneratedClass
//					
//				}
//				
//			}
//			//adds actor to swarm array
//			swarmArray.Push(SwAct);
//			
//		}
//	}
//}
//void AswarmController::ApplyBasicSwarming(float tick)
//{
//		FVector alignmentV = FVector().ZeroVector;
//		FVector cohesionV = FVector().ZeroVector;
//		FVector separationV = FVector().ZeroVector;
//		FVector boundV = FVector().ZeroVector;
//		FVector totalV = FVector().ZeroVector;
//		for (int i = 0; i < swarmArray.Num(); i++)
//				{
//					
//						//get results
//					if (SeparationOn)
//						separationV = separation(swarmArray[i]);
//					if (AlignmentOn)
//						alignmentV = alignment(swarmArray[i]);
//					if (CohesionOn)
//						cohesionV = cohesion(swarmArray[i]) / 10;// *Scatter(swarmArray[i]) / 10;
//					if (BoundariesOn)
//						boundV = Boundaries(swarmArray[i]);
//
//					//scale the returned values
//						separationV = separationV *scaleSep;
//						cohesionV = cohesionV *scaleCoh;
//						alignmentV = alignmentV * scaleAli;
//						float appliedSpeed = speed * tick;
//						
//						swarmArray[i]->velocity = (swarmArray[i]->velocity + separationV + cohesionV + alignmentV + boundV)*speed;
//						if (skeletalYN)
//						{
//							swarmArray[i]->move->Velocity = swarmArray[i]->velocity;
//							swarmArray[i]->move->bForceMaxAccel = true;
//						}
//									
//				}
//}
//FVector AswarmController::Boundaries(AswarmActor* b)
//{
//	
//	FVector Bound = FVector().ZeroVector;
//	if (b->GetActorLocation().X < MinX)
//	{
//		Bound.X = boundaryFix;
//	}
//	if (b->GetActorLocation().X > MaxX)
//	{
//		Bound.X = -boundaryFix;
//	}
//	if (b->GetActorLocation().Y < MinY)
//	{
//		Bound.Y = boundaryFix;
//	}
//	if (b->GetActorLocation().Y > MaxY)
//	{
//		Bound.Y = -boundaryFix;
//	}
//	if (b->GetActorLocation().Z < MinZ)
//	{
//		Bound.Z = boundaryFix;
//	}
//	if (b->GetActorLocation().Z > MaxZ)
//	{
//		Bound.Z = -boundaryFix;
//	}
//	return Bound;
//}
//FVector AswarmController::alignmentTwo(FVector b)
//{
//	FVector ali2 = FVector().ZeroVector;
//	for (int i = 0; i < velArray.Num(); i++)
//	{
//		if (b != velArray[i])
//		{
//			ali2 = ali2 + velArray[i];
//		}
//	}
//	return ali2 / velArray.Num() - 1;
//}
//float AswarmController::Scatter(AswarmActor* b)
//{
//	//if (FVector().Dist(b->GetActorLocation(), player->GetComponentLocation()) < 50)
//		{
//			return -1;
//		}
//	//else
//	{
//		return 1;
//	}
//	
//}