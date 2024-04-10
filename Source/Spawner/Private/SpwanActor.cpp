// Fill out your copyright notice in the Description page of Project Settings.


#include "SpwanActor.h"
#include "Components/BoxComponent.h"
#include  "Kismet/KismetMathLibrary.h"

// Sets default values
ASpwanActor::ASpwanActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	spwanBound = CreateDefaultSubobject <UBoxComponent>(TEXT("Spawn Location "));
	RootComponent = spwanBound;
	// spawn timer  min and max 
	spawnDelayLow = 1.0f;
	spawnDelayHigh = 5.0f;

}

// Called when the game starts or when spawned
void ASpwanActor::BeginPlay()
{
	Super::BeginPlay();
	// create the first spawn delay time 
	spawnDelay = FMath::FRandRange(spawnDelayLow, spawnDelayHigh);

	//set the timer and what function to call 
	GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpwanActor::SpawnItems, spawnDelay, false);
	
}

// Called every frame
void ASpwanActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBoxComponent* ASpwanActor::retSpawnLocation()
{
	return spwanBound;
	
}

// get the random location in the bound 
FVector ASpwanActor::retRandomPoints()
{
	FVector RandSpawnBegin = spwanBound->Bounds.Origin;
	FVector RandSpawnEnd = spwanBound->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(RandSpawnBegin, RandSpawnEnd);
}

void ASpwanActor::SpawnItems()
{
	// if there is anything to spawn 
	if (spawnActor != NULL)
	{
		//get the world 
		UWorld* const myWorld = GetWorld();
		if (myWorld)
		{
			FActorSpawnParameters SpawnParam;  // This structure is used to pass a variety of parameters when spawning a new actor in the game.
			SpawnParam.Owner = this; //set the owner of spawner to this actor 
			SpawnParam.Instigator = GetInstigator(); //The Instigator is the actor that caused this actor to spawn, usually the player character or AI that initiated the action causing the spawn. GetInstigator() is a function that retrieves the instigator of the current actor.
			FVector randLocations = retRandomPoints();
			FRotator randRotation;

			//random rotations 
			randRotation.Yaw = FMath::FRand() * 360.0f;
			randRotation.Roll = FMath::FRand() * 360.0f;
			randRotation.Pitch = FMath::FRand() * 360.0f;
			ADrop* const SpawnedDrop =	myWorld->SpawnActor< ADrop>(spawnActor, randLocations, randRotation, SpawnParam);
			spawnDelay = FMath::FRandRange(spawnDelayLow, spawnDelayHigh);
			GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpwanActor::SpawnItems, spawnDelay, false);
		}

	}

}

