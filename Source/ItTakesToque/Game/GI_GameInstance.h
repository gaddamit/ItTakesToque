// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ItTakesToque/Constants.h"
#include "GI_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ITTAKESTOQUE_API UGI_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UGI_GameInstance();
	UFUNCTION(BlueprintCallable, Category="Default")
	void SetCharacterType(int Player, ECharacterType Type);
	ECharacterType GetCharacterType(int Player) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	ECharacterType CharacterType1 = ECharacterType::KNIGHT;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	ECharacterType CharacterType2 = ECharacterType::MAGE;
public:
	UFUNCTION(BlueprintCallable, Category="Default")
	void PrintCharacterType() const;
private:
};
