// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Base.h"

UGA_Base::UGA_Base()
{
    // Set this ability to be activated by default
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;

    // Initialize the SkillIcon if needed
    SkillIcon = nullptr;
}

void UGA_Base::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}