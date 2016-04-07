// Fill out your copyright notice in the Description page of Project Settings.

#include "SwarmPlug.h"
#include "swarmActor.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
AswarmActor::AswarmActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetTickGroup(ETickingGroup::TG_PostPhysics);
	

	
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
	SetActorLocation(GetActorLocation() + velocity *  DeltaTime);
	actor->SetActorLocation(GetActorLocation());
	//SetActorLocation(GetActorLocation() + velocity * DeltaTime);
	velocity = velocity.GetClampedToSize(0, 360);
	SetActorRotation(velocity.Rotation());
	actor->SetActorRotation(GetActorRotation());
	///LineTracer();

}


FVector AswarmActor::LineTracer()
{
	FVector line = FVector().ZeroVector;

	if (actor)
	{

		FVector pos;
		FRotator rot;
		actor->GetActorEyesViewPoint(pos, rot);
		ECollisionChannel trace = ECollisionChannel::ECC_MAX;
		const FName TraceTag("Trace");
		GetWorld()->DebugDrawTraceTag = TraceTag;
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);
		params.AddIgnoredActor(actor);
		params.TraceTag = TraceTag;
		pos.Z -= 10;
		FHitResult hit;
		FVector end = pos + (rot.Vector() * 200);

		GetWorld()->LineTraceSingleByChannel(hit, pos, end, trace, params);
		line = hit.Location;
	}
	return -(line / 100);
}
void AswarmActor::SpawnActors(UClass* cl)
{
	UWorld* world = GetWorld();
	if (world)
	{
		actor = world->SpawnActor<AActor>(cl,GetActorLocation(),GetActorRotation());
		//actor->AttachRootComponentToActor(this);
	}
}