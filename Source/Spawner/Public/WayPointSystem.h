///
// an actor to be spawn as one of the elemnts of the array of waypoints 
/// 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WayPointSystem.generated.h"

UCLASS()
class SPAWNER_API AWayPointSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWayPointSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
