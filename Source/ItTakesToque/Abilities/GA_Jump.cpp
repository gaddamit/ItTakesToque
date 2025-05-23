// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Jump.h"
#include "GameFramework/Character.h"

UGA_Jump::UGA_Jump()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Jump::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor))
    {
        Character->Jump();
        UE_LOG(LogTemp, Log, TEXT("Jump ability activated"));
    }
    
    EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}