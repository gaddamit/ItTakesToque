// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelActorSpawner.h"
#include "NavigationSystem.h"
#include "Components/SphereComponent.h"

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
		if(SpawnStart)
		{
			SpawnActors();
			if(bIsLooping)
			{
				GetWorld()->GetTimerManager().SetTimer(SpawnerTimerHandle, this, &ALevelActorSpawner::SpawnActors, SpawnInterval, bIsLooping);
			}
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
	if(bEnabled)
	{
		return;
	}
	
	bEnabled = true;
	
	if(SpawnerTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnerTimerHandle);
	}

	GetWorld()->GetTimerManager().SetTimer(SpawnerTimerHandle, this, &ALevelActorSpawner::SpawnActors, SpawnInterval, bIsLooping, SpawnStart);
}

void ALevelActorSpawner::Deactivate(bool bShouldDestroy)
{
	bEnabled = false;
	if(SpawnerTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnerTimerHandle);
	}

	if(bShouldDestroy)
	{
		Destroy();
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
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	
	for(int i = 0; i < NumberOfActorsToSpawn; ++i)
	{
		int tries = 5;
		int32 RandomIndex = FMath::RandRange(0, range-1);
		float RandomRotation = IsRotationRandom ? FMath::FRandRange(0.0f, 360.0f) : GetActorRotation().Yaw;
		FRotator Rotator = FRotator(0, RandomRotation, 0);

		AActor* SpawnedActor = nullptr;
		do
		{
			tries--;
			SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorsToSpawn[RandomIndex], GetRandomSpawnLocation(), Rotator, SpawnParams);
		} while (tries > 0 && !SpawnedActor);

		#if WITH_EDITOR
		if(SpawnedActor)
		{
			SpawnedActor->SetFolderPath(FName("Enemies"));
		}
		#endif
	}

	OnSpawnComplete();
}

FVector ALevelActorSpawner::GetRandomSpawnLocation() const
{
    FVector Location = GetActorLocation() + FVector(0,0,50.0f);
    float Scale = GetActorScale3D().X;
	FNavLocation RandomLocation;
	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	//USphereComponent* Sphere = Cast<USphereComponent>(SphereMesh);
	if(NavSystem && NavSystem->GetRandomReachablePointInRadius(Location, Scale, RandomLocation))
	{
		RandomLocation.Location.Z = abs(RandomLocation.Location.Z);
		return RandomLocation.Location;
	}

	return Location;
}