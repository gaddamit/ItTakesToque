// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Base.h"
#include "GA_Jump.generated.h"

/**
 * 
 */
UCLASS()
class ITTAKESTOQUE_API UGA_Jump : public UGA_Base
{
	GENERATED_BODY()

	public:
	UGA_Jump();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

};
