// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Cancel.generated.h"

/**
 * 
 */
UCLASS()
class ITTAKESTOQUE_API UGA_Cancel : public UGameplayAbility
{
	GENERATED_BODY()
	
	public:
	UGA_Cancel();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
