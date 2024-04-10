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
	// spawn timer 
	spawnDelayLow = 1.0f;
	spawnDelayHigh = 5.0f;

}

// Called when the game starts or when spawned
void ASpwanActor::BeginPlay()
{
	Super::BeginPlay();
	spawnDelay = FMath::FRandRange(spawnDelayLow, spawnDelayHigh);
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

FVector ASpwanActor::retRandomPoints()
{
	FVector RandSpawnBegin = spwanBound->Bounds.Origin;
	FVector RandSpawnEnd = spwanBound->Bounds.BoxExtent;
	return UKismetMathLibrary::RandomPointInBoundingBox(RandSpawnBegin, RandSpawnEnd);
}

void ASpwanActor::SpawnItems()
{
	if (spawnActor != NULL)
	{
		UWorld* const myWorld = GetWorld();
		if (myWorld)
		{
			FActorSpawnParameters SpawnParam;
			SpawnParam.Owner = this;
			SpawnParam.Instigator = GetInstigator();
			FVector randLocations = retRandomPoints();
			FRotator randRotation;
			randRotation.Yaw = FMath::FRand() * 360.0f;
			randRotation.Roll = FMath::FRand() * 360.0f;
			randRotation.Pitch = FMath::FRand() * 360.0f;
			ADrop* const SpawnedDrop =	myWorld->SpawnActor< ADrop>(spawnActor, randLocations, randRotation, SpawnParam);
			spawnDelay = FMath::FRandRange(spawnDelayLow, spawnDelayHigh);
			GetWorldTimerManager().SetTimer(spawnTimer, this, &ASpwanActor::SpawnItems, spawnDelay, false);
		}

	}

}

