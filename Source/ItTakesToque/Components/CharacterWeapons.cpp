// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterWeapons.h"
#include "../ItTakesToqueCharacter.h"
#include "../Weapon.h"

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
}

void UCharacterWeapons::OnCollect(AActor* Collector)
{
    Super::OnCollect(Collector);
    
    // Implement the logic for switching characters
    // For example, you might want to change the player's character or update the game state

    AItTakesToqueCharacter* PlayerCharacter = Cast<AItTakesToqueCharacter>(Collector);
    if (!PlayerCharacter)
    {
        UE_LOG(LogTemp, Warning, TEXT("Collector is not a valid player character"));
        return;
    }

    UCharacterWeapons* CW = PlayerCharacter->GetCharacterWeapons();
    if (!CW)
    {
        UE_LOG(LogTemp, Warning, TEXT("Collector is not a valid player character 2 "));
        return;
    }

    // Logic to switch weapons or update the player's weapon inventory
    UMeshComponent* MC = PlayerCharacter->GetMesh();
    if(!MC)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player character does not have a valid mesh component 3"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Equipping weapons for %s"), *PlayerCharacter->GetName());
    UE_LOG(LogTemp, Warning, TEXT("Weapons count: %d"), Weapons.Num());

    UE_LOG(LogTemp, Warning, TEXT("EquippedWeapons count: %d"), CW->EquippedWeapons.Num());

    for (const auto& WeaponPair : CW->EquippedWeapons)
    {
        FString SocketName = WeaponPair.Key;
        AWeapon* EquippedWeapon = WeaponPair.Value;

        if (EquippedWeapon)
        {
            EquippedWeapon->Destroy();
            UE_LOG(LogTemp, Warning, TEXT("Removed weapon from socket %s"), *SocketName);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Equipped weapon is not valid for socket %s"), *SocketName);
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
            //NewWeapon->AttachToComponent(MC, FAttachmentTransformRules::SnapToTargetIncludingScale, FName(*SocketName));
            //Set Location Rule to SnapToTarget but rotation and scale keeprelative
            FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, EAttachmentRule::KeepRelative, true);
            NewWeapon->AttachToComponent(MC, AttachmentRules, FName(*SocketName));
            CW->EquippedWeapons.Add(SocketName, NewWeapon);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Weapon class is not valid for socket %s"), *SocketName);
            continue;
        }
    }
}
