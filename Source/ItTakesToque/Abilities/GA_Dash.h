// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Base.h"
#include "GA_Dash.generated.h"

/**
 * 
 */
UCLASS()
class ITTAKESTOQUE_API UGA_Dash : public UGA_Base
{
	GENERATED_BODY()
	
	public:
	UGA_Dash();
	//virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

};
