#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ECharacterType : uint8
{
	NONE		UMETA(DisplayName = "None"),
    KNIGHT      UMETA(DisplayName = "Knight"),
    BARBARIAN	UMETA(DisplayName = "Barbarian"),
    ROGUE		UMETA(DisplayName = "Rogue"),
	MAGE		UMETA(DisplayName = "Mage"),
    UNDEAD      UMETA(DisplayName = "Undead"),
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
    Skill1      UMETA(DisplayName = "Skill1"),
    Skill2      UMETA(DisplayName = "Skill2"),
    Skill3      UMETA(DisplayName = "Skill3"),
};

enum class ETeams : uint8
{
	HUMAN UMETA(DisplayName = "Human"),
	UNDEAD UMETA(DisplayName = "Undead"),
	NONE = 255 UMETA(DisplayName = "None"),
};

#define COLLISION_OBJECT_FRIEND ECC_GameTraceChannel1
#define COLLISION_OBJECT_ENEMY  ECC_GameTraceChannel2
