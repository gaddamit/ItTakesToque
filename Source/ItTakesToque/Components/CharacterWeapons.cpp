// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWeapons.h"
#include "../ItTakesToqueCharacter.h"
#include "../Weapon.h"

DEFINE_LOG_CATEGORY(LogWeapons);

UCharacterWeapons::UCharacterWeapons()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterWeapons::BeginPlay()
{
    Super::BeginPlay();
    
    // Initialize or load any necessary data for weapons here
    // For example, you might want to load weapon classes or set up default weapons
    UE_LOG(LogWeapons, Warning, TEXT("UCharacterWeapons::BeginPlay called for %s"), *GetOwner()->GetName());
}


void UCharacterWeapons::OnCollect(AActor* Collector)
{
    Super::OnCollect(Collector);
    
    // Implement the logic for switching characters
    // For example, you might want to change the player's character or update the game state

    AItTakesToqueCharacter* PlayerCharacter = Cast<AItTakesToqueCharacter>(Collector);
    if (!PlayerCharacter)
    {
        UE_LOG(LogWeapons, Warning, TEXT("Collector is not a valid player character"));
        return;
    }

    UpdateWeapons(PlayerCharacter, true);
}

void UCharacterWeapons::UpdateWeapons(AItTakesToqueCharacter* PlayerCharacter, bool bForceUpdate)
{
    UE_LOG(LogWeapons, Warning, TEXT("Updating weapons for %s"), *PlayerCharacter->GetName());

    UCharacterWeapons* CW = PlayerCharacter->GetCharacterWeapons();
    if (!CW)
    {
        UE_LOG(LogWeapons, Warning, TEXT("Not a valid player character."));
        return;
    }

    // Logic to switch weapons or update the player's weapon inventory
    UMeshComponent* MC = PlayerCharacter->GetMesh();
    if(!MC)
    {
        UE_LOG(LogWeapons, Warning, TEXT("Player character does not have a valid mesh component."));
        return;
    }

    if (bForceUpdate)
    {
        CW->Weapons.Empty();
        CW->Weapons = Weapons;
    }

    // Remove all currently equipped weapons
    for (const auto& WeaponPair : CW->EquippedWeapons)
    {
        FString SocketName = WeaponPair.Key;
        AWeapon* EquippedWeapon = WeaponPair.Value;

        if (EquippedWeapon)
        {
            EquippedWeapon->Destroy();
            UE_LOG(LogWeapons, Warning, TEXT("Removed weapon from socket %s"), *SocketName);
        }
        else
        {
            UE_LOG(LogWeapons, Warning, TEXT("Equipped weapon is not valid for socket %s"), *SocketName);
        }
    }

    CW->EquippedWeapons.Empty();

    for (const auto& WeaponPair : Weapons)
    {
        FString SocketName = WeaponPair.Key;
        TSubclassOf<AWeapon> WeaponClass = WeaponPair.Value;

        if (WeaponClass)
        {
            AWeapon* NewWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator);
            FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
            NewWeapon->AttachToComponent(MC, AttachmentRules, FName(*SocketName));
            CW->EquippedWeapons.Add(SocketName, NewWeapon);
        }
        else
        {
            UE_LOG(LogWeapons, Warning, TEXT("Weapon class is not valid for socket %s"), *SocketName);
            continue;
        }
    }
}
