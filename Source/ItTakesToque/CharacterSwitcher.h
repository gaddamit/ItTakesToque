// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollectibleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "CharacterSwitcher.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	NONE		UMETA(DisplayName = "None"),
    KNIGHT      UMETA(DisplayName = "Knight"),
    BARBARIAN	UMETA(DisplayName = "Barabarian"),
    ROGUE		UMETA(DisplayName = "Rogue"),
	MAGE		UMETA(DisplayName = "Mage"),
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ITTAKESTOQUE_API UCharacterSwitcher : public UCollectibleComponent
{
	GENERATED_BODY()
	public:
	virtual void OnCollect(AActor* Collector) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ECharacterType CharacterType = ECharacterType::NONE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	USkeletalMesh* SkeletalMeshAsset = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TSubclassOf<UAnimInstance> NewAnimClass = nullptr;
};
