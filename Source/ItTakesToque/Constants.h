#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	NONE		UMETA(DisplayName = "None"),
    KNIGHT      UMETA(DisplayName = "Knight"),
    BARBARIAN	UMETA(DisplayName = "Barabarian"),
    ROGUE		UMETA(DisplayName = "Rogue"),
	MAGE		UMETA(DisplayName = "Mage"),
};

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
    None        UMETA(DisplayName = "None"),
    Confirm     UMETA(DisplayName = "Confirm"),
    Cancel      UMETA(DisplayName = "Cancel"),
    Jump        UMETA(DisplayName = "Jump"),
    Dash        UMETA(DisplayName = "Dash"),
    Interact    UMETA(DisplayName = "Interact"),
    IA_Skill1      UMETA(DisplayName = "Skill1"),
    Skill2      UMETA(DisplayName = "Skill2"),
    Skill3      UMETA(DisplayName = "Skill3"),
};
