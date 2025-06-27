// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GM_Coop.generated.h"

/**
 * 
 */
UCLASS()
class ITTAKESTOQUE_API AGM_Coop : public AGameModeBase
{
	GENERATED_BODY()
public:
	AGM_Coop();
	virtual void BeginPlay() override;
protected:
};
