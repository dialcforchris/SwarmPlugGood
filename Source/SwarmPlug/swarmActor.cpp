// Fill out your copyright notice in the Description page of Project Settings.

#include "SwarmPlug.h"
#include "swarmActor.h"

// Sets default values
AswarmActor::AswarmActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FName compName = "Mesh";
	AddComponent(compName, false, GetTransform(), mesh);

	velocity = FVector(0, 0, 0);
	TArray<UStaticMeshComponent*> components;
	GetComponents<UStaticMeshComponent>(components);
	for (int32 i = 0; i<components.Num(); i++)
	{
		//SM_Comp = components[i];
		UStaticMeshComponent* SM_Comp = components[i];
		SM_Comp->StaticMesh = mesh;
	}

	
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
	
	velocity = velocity.GetClampedToSize(0, 360);
	SetActorRotation(velocity.Rotation());
	

}


FVector AswarmActor::LineTracer()
{
	FVector line = FVector().ZeroVector;
	TArray<UStaticMeshComponent*> components;
	UStaticMeshComponent* SM_Comp = NULL;
	FRotator rot;
	ECollisionChannel trace = ECollisionChannel::ECC_Visibility;
	const FName TraceTag("Trace");
	GetWorld()->DebugDrawTraceTag = TraceTag;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.TraceTag = TraceTag;

	GetComponents<UStaticMeshComponent>(components);
	for (int32 i = 0; i<components.Num(); i++)
	{
		SM_Comp = components[i];
		UStaticMesh* mesh = SM_Comp->StaticMesh;

	}
	rot = SM_Comp->GetComponentRotation() - GetActorRotation();

	
	FHitResult hit;
	FVector start = GetActorLocation();
	FVector end = (rot.Vector().ForwardVector + start)*10;
	//end.X += 10;
	//end = end + start;
	GetWorld()->LineTraceSingleByChannel(hit, start, end, trace, params);
	return GetActorLocation() +line / 100;
}
