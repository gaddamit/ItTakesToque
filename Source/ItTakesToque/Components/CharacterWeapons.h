// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectibleComponent.h"
#include "../Game/Weapon.h"
#include "CharacterWeapons.generated.h"

class AItTakesToqueCharacter;

DECLARE_LOG_CATEGORY_EXTERN(LogWeapons, Log, All);
/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ITTAKESTOQUE_API UCharacterWeapons : public UCollectibleComponent
{
	GENERATED_BODY()
	
	public:
		// Sets default values for this component's properties
		UCharacterWeapons();

		virtual void OnCollect(AActor* Collector) override;
	protected:
		// Called when the game starts
		virtual void BeginPlay() override;
	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
		TMap<FString, TSubclassOf<class AWeapon>> Weapons;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
		TMap<FString, AWeapon*> EquippedWeapons;
	public:
		/** Function to equip a weapon */
		UFUNCTION(BlueprintCallable, Category = "Weapons")
		void UpdateWeapons(AItTakesToqueCharacter* PlayerCharacter, bool bForceUpdate = false);
};
