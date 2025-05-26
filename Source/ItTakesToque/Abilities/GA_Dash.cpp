// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Dash.h"
#include "GameFramework/Character.h"

UGA_Dash::UGA_Dash()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

// void UGA_Dash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
// {
//     if (ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor))
//     {
        
//         UE_LOG(LogTemp, Log, TEXT("Ability activated"));
//     }
    
//     EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
// }