// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Drop.h"
#include "SpwanActor.generated.h"

UCLASS()
class SPAWNER_API ASpwanActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpwanActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	class UBoxComponent* retSpawnLocation();

	// spawn boundry box 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowAbstract = "true"))
	class UBoxComponent* spwanBound;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	FVector retRandomPoints();


	FTimerHandle spawnTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category =  "Spawning")
	float  spawnDelayLow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float  spawnDelayHigh;

private:
	float spawnDelay; 


//what to spawn 
public :
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class ADrop> spawnActor;  // what to drop/spawn 
	void SpawnItems();

};
