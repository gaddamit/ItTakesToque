// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSwitcher.h"
#include "ItTakesToqueCharacter.h"

void UCharacterSwitcher::OnCollect(AActor* Collector)
{
    Super::OnCollect(Collector);
    // Implement the logic for switching characters
    // For example, you might want to change the player's character or update the game state
    UE_LOG(LogTemp, Warning, TEXT("Character switched by %s"), *Collector->GetName());
    
    AItTakesToqueCharacter* PlayerCharacter = Cast<AItTakesToqueCharacter>(Collector);
    if (PlayerCharacter)
    {
        // Set the character type
        PlayerCharacter->CharacterType = CharacterType;
        UE_LOG(LogTemp, Warning, TEXT("Character type set to %s"), *UEnum::GetValueAsString(CharacterType));
        
        // Set the skeletal mesh
        if (SkeletalMeshAsset)
        {
            PlayerCharacter->GetMesh()->SetSkeletalMesh(SkeletalMeshAsset);
            PlayerCharacter->GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
            PlayerCharacter->GetMesh()->SetAnimInstanceClass(NewAnimClass);
            
            UE_LOG(LogTemp, Warning, TEXT("Skeletal mesh set to %s"), *SkeletalMeshAsset->GetName());
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Skeletal mesh asset not found"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Collector is not a valid player character"));

    }
}