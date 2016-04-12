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
	SetActorLocation(GetActorLocation() + velocity *  DeltaTime);
	actor->SetActorLocation(GetActorLocation());
	velocity = velocity.GetClampedToSize(0, 360);
	SetActorRotation(velocity.Rotation());
	actor->SetActorRotation(GetActorRotation());
	

}


void ATheSwarmActor::SpawnActors(UClass* cl)
{
	UWorld* world = GetWorld();
	if (world)
	{
		actor = world->SpawnActor<AActor>(cl, GetActorLocation(), GetActorRotation());
		
	}
}