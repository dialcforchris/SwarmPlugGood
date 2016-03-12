// Fill out your copyright notice in the Description page of Project Settings.

#include "SwarmPlug.h"
#include "swarmActor.h"

// Sets default values
AswarmActor::AswarmActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	velocity = FVector(0, 0, 0);

	
	// enum Behaviours behave; 
	behave = Behaviours::IDLE;
}

// Called when the game starts or when spawned
void AswarmActor::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AswarmActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + velocity * DeltaTime);
	//velocity += GetActorLocation();
	velocity = velocity.GetClampedToSize(0, 360);
	SetActorRotation(velocity.Rotation());
	

}



