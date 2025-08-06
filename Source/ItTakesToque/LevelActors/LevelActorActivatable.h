// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItTakesToque/Interfaces/IActivatable.h"
#include "LevelActorActivatable.generated.h"

UCLASS()
class ITTAKESTOQUE_API ALevelActorActivatable : public AActor, public IActivatable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelActorActivatable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Default")
	void Activate() override;

	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="Default")
	void Deactivate() override;
};
