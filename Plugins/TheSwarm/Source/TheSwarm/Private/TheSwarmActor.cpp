#pragma once
#include "TheSwarmPrivatePCH.h"

ATheSwarmActor::ATheSwarmActor(const class FObjectInitializer& PCIP) :Super(PCIP)
{
	velocity = FVector::ZeroVector;
	
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetTickGroup(ETickingGroup::TG_PostPhysics);
	 
	behave = Behaviours::IDLE;
}

// Called when the game starts or when spawned
void ATheSwarmActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATheSwarmActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UCapsuleComponent* move = NULL;
	TArray<UCapsuleComponent*>comps;
	actor->GetComponents(comps);
	if (comps.Num() > 0)
	{
		move = comps[0];
	}

	//adjust Z axis for allowing gravity
	FVector gravityFudge = FVector(GetActorLocation().X, GetActorLocation().Y, actor->GetActorLocation().Z);
	SetActorLocation(gravityFudge + velocity *  DeltaTime);

	//moves swarm actor and child actor
	actor->SetActorLocation(GetActorLocation());
	velocity = velocity.GetClampedToSize(0, 360);
	SetActorRotation(velocity.Rotation());
	actor->SetActorRotation(GetActorRotation());
	
	//allows animation assets to be used
	if (move != NULL)
	{
		move->SetAllPhysicsLinearVelocity(velocity);
	}

}


void ATheSwarmActor::SpawnActors(UClass* cl)
{
	UWorld* world = GetWorld();
	if (world)
	{
		actor = world->SpawnActor<AActor>(cl, GetActorLocation(), GetActorRotation());
		actor->AttachRootComponentToActor(this);
	}
}