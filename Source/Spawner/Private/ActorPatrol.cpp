// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPatrol.h"
#include "Components/BoxComponent.h"
// Sets default values
AActorPatrol::AActorPatrol()
{
 	PrimaryActorTick.bCanEverTick = true;

	CurrentWaypointIndex = 0;
	Speed = 30.0f;
    Waypoints.Empty();
    BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
    // Attach the collider to the RootComponent of the actor.
    BoxCollider->SetupAttachment(RootComponent);
  
}


void AActorPatrol::BeginPlay()
{
	Super::BeginPlay();
    if (Waypoints.IsEmpty()) {
        return;
    }
	
}

// Called every frame
void AActorPatrol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveToNextWaypoint(DeltaTime);

}

void AActorPatrol::MoveToNextWaypoint(float DeltaTime)
{
    if (Waypoints.Num() == 0)
        return;
    FVector CurrentLocation = GetActorLocation();  // get the currect actor location 
    FVector TargetLocation = Waypoints[CurrentWaypointIndex]->GetActorLocation();  // get the current waypoint location // starts from index 0 
    FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal(); // find the Normal direction that points to the target 

    FVector NewLocation = CurrentLocation + Direction * Speed * DeltaTime; // find the new location 


    // when we get close to the targe,  then change to the next way point 
    if (FVector::Dist(TargetLocation, CurrentLocation) < 100.0f)
    {
        CurrentWaypointIndex += 1;
        if (CurrentWaypointIndex >= Waypoints.Num())
        {
            CurrentWaypointIndex = 0;
        }
    }
    else {
        SetActorLocation(NewLocation);
    }
}

