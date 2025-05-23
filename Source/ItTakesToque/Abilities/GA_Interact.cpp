// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Interact.h"
#include "GameFramework/Character.h"

UGA_Interact::UGA_Interact()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor))
    {
        UE_LOG(LogTemp, Log, TEXT("Interact ability activated"));
    }
    
    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

