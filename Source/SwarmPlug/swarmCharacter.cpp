// Fill out your copyright notice in the Description page of Project Settings.

#include "SwarmPlug.h"
#include "swarmCharacter.h"


// Sets default values
AswarmCharacter::AswarmCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AswarmCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AswarmCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AswarmCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

