// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Components/Image.h"
#include "NiagaraSystem.h"
#include "GA_Base.generated.h"

/**
 * 
 */
UCLASS()
class ITTAKESTOQUE_API UGA_Base : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGA_Base();

	// Override the ActivateAbility function to implement custom ability logic
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category="Skill")
	float GetCooldownDuration();
public:
	// Skill Icon
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	UTexture2D* SkillIcon;

	// Animation Montage
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skill")
	UAnimMontage* SkillAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
	UNiagaraSystem* SkillEffect;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActivateAbility);

	UPROPERTY(BlueprintAssignable, Category="Events")
	FOnActivateAbility OnActivateAbility;
};
