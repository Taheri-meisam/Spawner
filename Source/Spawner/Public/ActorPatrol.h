// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WayPointSystem.h"
#include "ActorPatrol.generated.h"

UCLASS()
class SPAWNER_API AActorPatrol : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorPatrol();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:

    // Array of waypoints
	UPROPERTY(EditAnywhere, Category = "Waypoints")
	TArray<AWayPointSystem*> Waypoints;


	// moving from one way point to another 
	void MoveToNextWaypoint(float DeltaTime);
	// speed of the patrolling 
	UPROPERTY(EditAnywhere, Category = "Waypoints")
	float Speed;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* BoxCollider;


private:
	int32 CurrentWaypointIndex;


};
