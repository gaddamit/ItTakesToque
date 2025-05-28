// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../CollectibleComponent.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "../Constants.h"
#include "CharacterAbilities.generated.h"

class UInputAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ITTAKESTOQUE_API UCharacterAbilities : public UCollectibleComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterAbilities();
	virtual void OnCollect(AActor* Collector) override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ECharacterType CharacterType = ECharacterType::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TMap<TObjectPtr<UInputAction>, TSubclassOf<class UGameplayAbility>> Abilities;
};
