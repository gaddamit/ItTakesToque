// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Cancel.h"
#include "GameFramework/Character.h"

UGA_Cancel::UGA_Cancel()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Cancel::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor))
    {
        UE_LOG(LogTemp, Log, TEXT("Cancel ability activated"));
    }
    
    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

