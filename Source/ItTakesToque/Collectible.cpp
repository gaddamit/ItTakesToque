// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectible.h"
#include "Components/StaticMeshComponent.h"
#include "CollectibleComponent.h"

// Sets default values
ACollectible::ACollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
}

// Called when the game starts or when spawned
void ACollectible::BeginPlay()
{
	Super::BeginPlay();
	CollectibleMesh = FindComponentByClass<UStaticMeshComponent>();

	if (CollectibleMesh)
	{
		CollectibleMesh->OnComponentBeginOverlap.AddDynamic(this, &ACollectible::OnOverlapBegin);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SphereComponent not found"));
	}
}

// Called every frame
void ACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("Collectible Tick"));
}

void ACollectible::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap with %s"), *OtherActor->GetName());
		//get all components of type CollectibleComponent
		TArray<UCollectibleComponent*> CollectibleComponents;
		this->GetComponents<UCollectibleComponent>(CollectibleComponents);
		for (UCollectibleComponent* CollectibleComponent : CollectibleComponents)
		{
			CollectibleComponent->OnCollect(OtherActor);
		}
	}
}