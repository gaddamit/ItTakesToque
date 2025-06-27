// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelActorSpawner.h"
#include "NavigationSystem.h"

// Sets default values
ALevelActorSpawner::ALevelActorSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
    //RootComponent = SphereMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (SphereAsset.Succeeded())
    {
        SphereMesh->SetStaticMesh(SphereAsset.Object);
    	SphereMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
    }
}

// Called when the game starts or when spawned
void ALevelActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	if(bEnabled)
	{
		if(bSpawnOnStart)
		{
			SpawnActors();
		}
		if(bIsLooping)
		{
			GetWorld()->GetTimerManager().SetTimer(SpawnerTimerHandle, this, &ALevelActorSpawner::SpawnActors, SpawnInterval, bIsLooping);
		}
	}

	SetActorHiddenInGame(true);
}

// Called every frame
void ALevelActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelActorSpawner::Activate()
{
	bEnabled = true;
	
	if(bSpawnOnStart)
	{
		SpawnActors();
	}
	
	if(SpawnerTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnerTimerHandle);
	}

	if(bIsLooping)
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnerTimerHandle, this, &ALevelActorSpawner::SpawnActors, SpawnInterval, bIsLooping);
	}
}

void ALevelActorSpawner::SpawnActors() const
{
	if(!bEnabled)
	{
		return;
	}
	
	auto range = ActorsToSpawn.Num();
	if(range <= 0)
	{
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	for(int i = 0; i < NumberOfActorsToSpawn; ++i)
	{
		int32 RandomIndex = FMath::RandRange(0, range-1);
		float RandomRotation = FMath::FRandRange(0.0f, 360.0f);
		FRotator Rotator = FRotator(0, RandomRotation, 0);
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorsToSpawn[RandomIndex], GetRandomSpawnLocation(), Rotator, SpawnParams);
		if(SpawnedActor)
		{
			SpawnedActor->SetFolderPath(FName("Enemies"));
		}
	}

	OnSpawnComplete();
}

FVector ALevelActorSpawner::GetRandomSpawnLocation() const
{
    FVector Location = GetActorLocation() + FVector(0,0,100.0f);
    float Scale = GetActorScale3D().X;
	FNavLocation RandomLocation;
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	if(NavSystem && NavSystem->GetRandomReachablePointInRadius(Location, Scale * 50.0f, RandomLocation))
	{
		return RandomLocation.Location;
	}

	return Location;
}