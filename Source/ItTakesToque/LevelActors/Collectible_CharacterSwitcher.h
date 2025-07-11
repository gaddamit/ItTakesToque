// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Collectible.h"
#include "../Components/CharacterSwitcher.h"
#include "../Components/CharacterAbilities.h"
#include "../Components/CharacterWeapons.h"
#include "Collectible_CharacterSwitcher.generated.h"

/**
 * 
 */
UCLASS()
class ITTAKESTOQUE_API ACollectible_CharacterSwitcher : public ACollectible
{
	GENERATED_BODY()
	public:
	ACollectible_CharacterSwitcher();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ECharacterType CharacterType = ECharacterType::NONE;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	FLinearColor CharacterColor = FLinearColor::White;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	class UNiagaraSystem* CharacterSwitchEffect = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UCharacterSwitcher* CharacterSwitcher = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilites")
	class UCharacterAbilities* CharacterAbilities = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	class UCharacterWeapons* CharacterWeapons = nullptr;

	protected:
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "MyEvents")
    void OverlapEffects(AActor* OtherActor);
};
