// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectible_CharacterSwitcher.h"
#include "ItTakesToqueCharacter.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ACollectible_CharacterSwitcher::ACollectible_CharacterSwitcher()
{
    // Initialize the CharacterSwitcher and CharacterAbilities components
    CharacterSwitcher = CreateDefaultSubobject<UCharacterSwitcher>(TEXT("CharacterSwitcher"));
    CharacterAbilities = CreateDefaultSubobject<UCharacterAbilities>(TEXT("CharacterAbilities"));
    CharacterWeapons = CreateDefaultSubobject<UCharacterWeapons>(TEXT("CharacterWeapons"));
}

void ACollectible_CharacterSwitcher::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
    if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap with %s"), *OtherActor->GetName());

        // Check if the OtherActor is of type AItTakesToqueCharacter   
        AItTakesToqueCharacter* Character = Cast<AItTakesToqueCharacter>(OtherActor);
        if (!Character)
        {
            return;
            
        }

        if(Character->CharacterType == ECharacterType::UNDEAD)
        {
            return; // Do not apply ability if character is undead
        }

        if(Character->CharacterType == CharacterType)
        {
            UE_LOG(LogTemp, Warning, TEXT("Character %s is same type."), *Character->GetName());
            return; // Character already has this ability, do not apply again
        }

        Character->CharacterType = CharacterType;

		//get all components of type CollectibleComponent
		TArray<UCollectibleComponent*> CollectibleComponents;
		this->GetComponents<UCollectibleComponent>(CollectibleComponents);
		for (UCollectibleComponent* CollectibleComponent : CollectibleComponents)
		{
			CollectibleComponent->OnCollect(OtherActor);
		}

        OverlapEffects(OtherActor);
        UNiagaraComponent* Indicator = Character->FindComponentByClass<UNiagaraComponent>();
        if (!Indicator)
        {
            UE_LOG(LogTemp, Warning, TEXT("NiagaraSystem not found on character %s"), *Character->GetName());
        }

        Indicator->SetColorParameter(FName("User.Ring Color"), CharacterColor);

        if(!CharacterSwitchEffect)
        {
            UE_LOG(LogTemp, Warning, TEXT("CharacterSwitchEffect is not set for %s"), *GetName());
        }
        else
        {
            UNiagaraComponent* Effect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), CharacterSwitchEffect, GetActorLocation(), FRotator::ZeroRotator);
            if(Effect)
            {
                Effect->SetColorParameter(FName("ColorStart"), CharacterColor);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to spawn CharacterSwitchEffect for %s"), *GetName());
            }
        }
	}
}