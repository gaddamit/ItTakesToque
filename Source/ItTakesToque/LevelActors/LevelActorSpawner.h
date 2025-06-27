// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/IActivatable.h"
#include "LevelActorSpawner.generated.h"

UCLASS()
class ITTAKESTOQUE_API ALevelActorSpawner : public AActor, public IActivatable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelActorSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	bool bEnabled = true; // Whether the spawner is enabled or not

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TArray<TSubclassOf<AActor>> ActorsToSpawn; // Array of actor classes to spawn

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	int32 NumberOfActorsToSpawn = 1; // Number of actors to spawn at once

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float SpawnInterval = 1.0f; // Time interval between spawns in seconds

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	bool bSpawnOnStart = true; // Whether to spawn actors when the game starts

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	bool bIsLooping = false; // Whether to keep spawning actors in a loop

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Spawner")
	UStaticMeshComponent* SphereMesh; // Mesh component for the spawner
private:
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Activate() override; // Implementation of IActivatable interface

	UFUNCTION(BlueprintImplementableEvent, Category = "MyEvents")
	void OnSpawnComplete() const;
private:
	FTimerHandle SpawnerTimerHandle;
	void SpawnActors() const;
	FVector GetRandomSpawnLocation() const; // Helper function to get a random spawn location within the spawner's bounds
};
