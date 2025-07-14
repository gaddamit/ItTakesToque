// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "../Interfaces/IInteractable.h"
#include "LevelInteractor.generated.h"

class UWidgetComponent;
UCLASS()
class ITTAKESTOQUE_API ALevelInteractor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelInteractor();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Default")
	USphereComponent* SphereCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	TArray<AActor*> ActorsToActivate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Default")
	UWidgetComponent* InteractUI;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Default")
	UInputAction* InputAction;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable, Category="Default")
	virtual void Interact() override;
private:
	UGA_Base* Ability;
};
