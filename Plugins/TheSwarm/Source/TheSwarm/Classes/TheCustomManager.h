#pragma once

#include "Engine.h"
#include "TheSwarmManager.h"
#include "TheSwarmManagerAnimal.h"
#include "TheCustomManager.generated.h"


UCLASS()
class THESWARM_API ATheCustomManager : public ATheSwarmManagerAnimal
{

	GENERATED_UCLASS_BODY()

public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	
};
