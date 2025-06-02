// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_BasicProjectile.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "../ItTakesToqueCharacter.h"
#include "Kismet/GameplayStatics.h"

UGA_BasicProjectile::UGA_BasicProjectile()
{
    // Set this ability to be activated by default
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_BasicProjectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    // Implement the logic for launching a basic projectile here
    // For example, you might spawn a projectile actor and set its velocity
    if(!ActorInfo->AvatarActor.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Avatar Actor"));
        return;
    }
    AActor* AvatarActor = ActorInfo->AvatarActor.Get();
    if(!ProjectileClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Projectile Class is not set"));
        return;
    }

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItTakesToqueCharacter::StaticClass(), FoundActors);

    AItTakesToqueCharacter* ClosestEnemy = nullptr;
    float ClosestDistance = FLT_MAX;
    for (AActor* Actor : FoundActors)
    {
        AItTakesToqueCharacter* Enemy = Cast<AItTakesToqueCharacter>(Actor);
        if (Enemy && Enemy->CharacterType != ECharacterType::UNDEAD)
        {
            continue;
        }

        if(Enemy->CharacterAttributeSet->Health.GetCurrentValue() <= 0.0f)
        {
            // Skip dead enemies
            continue;
        }

        // Find closest enemy
        FVector EnemyLocation = Enemy->GetActorLocation();
        FVector AvatarLocation = AvatarActor->GetActorLocation();
        float DistanceToEnemy = FVector::Dist(AvatarLocation, EnemyLocation);
        if(DistanceToEnemy < ClosestDistance)
        {
            ClosestDistance = DistanceToEnemy;
            ClosestEnemy = Enemy;
        }
    }

    FTransform SpawnTransform = AvatarActor->GetTransform();
    if(IsValid(ClosestEnemy))
    {
        FVector DirectionToEnemy = (ClosestEnemy->GetActorLocation() - AvatarActor->GetActorLocation()).GetSafeNormal();
        AvatarActor->SetActorRotation(DirectionToEnemy.Rotation()); // Rotate towards the closest enemy
        SpawnTransform.SetRotation(AvatarActor->GetActorRotation().Quaternion()); // Set rotation to match the character's rotation
        SpawnTransform.SetLocation(AvatarActor->GetActorLocation() + AvatarActor->GetActorForwardVector() * 200.0f); // Adjust spawn location
    }
    else
    {
        SpawnTransform.SetLocation(AvatarActor->GetActorLocation() + AvatarActor->GetActorForwardVector() * 200.0f); // Adjust spawn location
        SpawnTransform.SetRotation(AvatarActor->GetActorRotation().Quaternion()); // Set rotation to match the character's rotation
    }
    AActor* SpawnedProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform);
    if(!SpawnedProjectile)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to spawn projectile"));
        return;
    }

    // Set the projectile's velocity
    FVector LaunchDirection = AvatarActor->GetActorForwardVector();
    FVector LaunchVelocity = LaunchDirection * ProjectileSpeed;

    // Assuming the projectile has a movement component, set its velocity
    UProjectileMovementComponent* ProjectileMovement = SpawnedProjectile->FindComponentByClass<UProjectileMovementComponent>();
    if(ProjectileMovement)
    {
        ProjectileMovement->Velocity = LaunchVelocity;
        ProjectileMovement->InitialSpeed = ProjectileSpeed;
        ProjectileMovement->MaxSpeed = ProjectileSpeed;
        ProjectileMovement->bShouldBounce = false; // Set to true if you want the projectile to bounce
        ProjectileMovement->ProjectileGravityScale = 0.0f; // Set to 1.0f for gravity effect
    }
    UE_LOG(LogTemp, Warning, TEXT("Basic Projectile Ability Activated"));

    OnAbilityActivated(); // Call the Blueprint event to notify that the ability was activated

    //EndAbility(Handle, ActorInfo, ActivationInfo, true, false); // End the ability after launching the projectile
}