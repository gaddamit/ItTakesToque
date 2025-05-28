// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectibleComponent.h"

// Sets default values for this component's properties
UCollectibleComponent::UCollectibleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCollectibleComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCollectibleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCollectibleComponent::OnCollect(AActor* Collector)
{
	// Implement the logic for what happens when the collectible is collected
	// For example, you might want to destroy the collectible or add it to the collector's inventory
	UE_LOG(LogTemp, Warning, TEXT("Collected by %s"), *Collector->GetName());
}
