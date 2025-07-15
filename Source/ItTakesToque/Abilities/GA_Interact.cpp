// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_Interact.h"
#include "GameFramework/Character.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

UGA_Interact::UGA_Interact()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_Interact::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
    
    if (ACharacter* Character = Cast<ACharacter>(ActorInfo->AvatarActor))
    {
        UE_LOG(LogTemp, Log, TEXT("Interact ability activated"));
        if(SkillAnimation)
        {
            UAbilityTask_PlayMontageAndWait* PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, FName("None"), SkillAnimation, 1.0f, FName("None"));  
            if (PlayMontageTask)
            {
                PlayMontageTask->OnCompleted.AddDynamic(this, &UGA_Interact::OnMontageCompleted);
                PlayMontageTask->OnInterrupted.AddDynamic(this, &UGA_Interact::OnMontageCompleted);
                PlayMontageTask->OnCancelled.AddDynamic(this, &UGA_Interact::OnMontageCompleted);
                PlayMontageTask->ReadyForActivation();
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to create PlayMontageAndWait task"));
            }
        }
    }
}

void UGA_Interact::OnMontageCompleted()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}
