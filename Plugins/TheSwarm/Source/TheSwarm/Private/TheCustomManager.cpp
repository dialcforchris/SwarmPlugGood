#pragma once
#include "TheSwarmPrivatePCH.h"

ATheCustomManager::ATheCustomManager(const class FObjectInitializer& PCIP) :Super(PCIP)
{
	PrimaryActorTick.bCanEverTick = true;
	/////////////////////////
	//set variables to zero
	/////////////////////////
	
	////cone trace variables
	//traceLength = 0;
	//radius = 0;
	//renderConeTrace = false;
	////swarming variables
	//speed = 0;
	//swarmSize = 0;
	//scaleSep = 0;
	//scaleAli = 0;
	//scaleCoh = 0;
	//maxDist = 0;
	//speed = 0;
	////boundaries variables
	//MaxX = 0;
	//MinX = 0;
	//MaxY = 0;
	//MinY = 0;
	//canFly = false;
	//MaxZ = 0;
	//MinZ = 0;
	//boundaryFix = 0;
	//player avoidance variables
    playerDistance = 0;
	playerAvoidance = 0;


}
void ATheCustomManager::BeginPlay()
{
	Super::BeginPlay();
	player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	box = NULL;

}
void ATheCustomManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	targetLocation = target->GetActorLocation();
	arraySize = swarmArray.Num();

}

