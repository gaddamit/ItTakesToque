// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_BasicMelee.h"
#include "GameFramework/Character.h"

UGA_BasicMelee::UGA_BasicMelee()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_BasicMelee::InputPressed(const FGameplayAbilitySpecHandle Handle,
                              const FGameplayAbilityActorInfo* ActorInfo,
                              const FGameplayAbilityActivationInfo ActivationInfo)
{
    Super::InputPressed(Handle, ActorInfo, ActivationInfo);

    // Ability is still active - do something again
    if (IsActive())
    {
        OnInputPressed();
    }
}