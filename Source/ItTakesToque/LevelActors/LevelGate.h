// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItTakesToque/Interfaces/IActivatable.h"
#include "Components/SphereComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "LevelGate.generated.h"

class UNiagaraComponent;

UCLASS()
class ITTAKESTOQUE_API ALevelGate : public AActor, public IActivatable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelGate();

	virtual void Activate() override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "MyEvents")
	void OnActivate();
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Default")
	USphereComponent* SphereCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level")
	FName LevelNameToLoad;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level")
	bool IsActivated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level")
	UNiagaraComponent* GateEffect;
private:
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
private:
};
