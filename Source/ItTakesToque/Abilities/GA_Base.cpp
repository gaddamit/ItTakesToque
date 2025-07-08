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

    CommitAbilityCooldown(Handle, ActorInfo, ActivationInfo, false);
    OnActivateAbility.Broadcast();
    UE_LOG(LogTemp, Warning, TEXT("OnActivateAbility Broadcast"));
    
}

float UGA_Base::GetCooldownDuration()
{
    float Duration = 0;

    UGameplayEffect* CooldownGE = GetCooldownGameplayEffect();
    if (CooldownGE)
    {
        const FGameplayEffectModifierMagnitude& DurationMagnitude = CooldownGE->DurationMagnitude;

        if (DurationMagnitude.GetMagnitudeCalculationType() == EGameplayEffectMagnitudeCalculation::ScalableFloat)
        {
            DurationMagnitude.GetStaticMagnitudeIfPossible(1, Duration);
            UE_LOG(LogTemp, Log, TEXT("Cooldown duration (from GE): %f seconds"), Duration);
        }
    }

    return Duration;
}
