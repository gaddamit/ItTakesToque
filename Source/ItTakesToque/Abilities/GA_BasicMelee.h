// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Base.h"
#include "GA_BasicMelee.generated.h"

/**
 * 
 */
UCLASS()
class ITTAKESTOQUE_API UGA_BasicMelee : public UGA_Base
{
	GENERATED_BODY()
	
	public:
	UGA_BasicMelee();

	UFUNCTION(BlueprintImplementableEvent, Category = "MyEvents")
    void OnInputPressed();
	
	// Called when the ability is activated
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle,
	                          const FGameplayAbilityActorInfo* ActorInfo,
	                          const FGameplayAbilityActivationInfo ActivationInfo) override;
};
