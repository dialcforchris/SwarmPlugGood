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
	
	actor->SetActorLocation(GetActorLocation());
	velocity = velocity.GetClampedToSize(0, 360);
	SetActorRotation(velocity.Rotation());
	actor->SetActorRotation(GetActorRotation());
	
	
	if (move != NULL)
	{
		move->SetAllPhysicsLinearVelocity(velocity);
	}
	

}


FVector AswarmActor::LineTracer()
{
	FVector line = FVector().ZeroVector;

	//if (actor)
	//{

	//	FVector pos;
	//	FRotator rot;
	//	actor->GetActorEyesViewPoint(pos, rot);
	//	
	//	ECollisionChannel trace = ECollisionChannel::ECC_MAX;
	//	const FName TraceTag("Trace");
	//	GetWorld()->DebugDrawTraceTag = TraceTag;
	//	FCollisionQueryParams params;
	//	params.AddIgnoredActor(this);
	//	params.AddIgnoredActor(actor);
	//	params.TraceTag = TraceTag;
	//	pos.Z -= 10;
	//	FHitResult hit;
	//	rot.Pitch = 0;
	//	rot.Roll = 0;
	//	FVector randomCone = FMath::VRandCone(rot.Vector(), 0.25);
	//	//randomCone.Z = 0;
	//	///randomCone.Y = 0;
	//	FVector end = pos + (randomCone * 200);// (rot.Vector() * 200);

	//	GetWorld()->LineTraceSingleByChannel(hit, pos, end, trace, params);
	//	line -= hit.ImpactPoint;
	//	
	//	{
	//		//return line;
	//	}
	//}

	return line/20;// -GetActorLocation());
}
void AswarmActor::SpawnActors(UClass* cl)
{
	UWorld* world = GetWorld();
	if (world)
	{
		actor = world->SpawnActor<AActor>(cl,GetActorLocation(),GetActorRotation());
		actor->AttachRootComponentTo(this->GetRootComponent());
	}
}