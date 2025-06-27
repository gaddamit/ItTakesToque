// Fill out your copyright notice in the Description page of Project Settings.


#include "GA_BasicProjectile.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Components/SphereComponent.h"

#include "../Character/ItTakesToqueCharacter.h"
#include "../Constants.h"


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

    if(!ProjectileClass)
    {
        UE_LOG(LogTemp, Warning, TEXT("Projectile Class is not set"));
        return;
    }

    AActor* AvatarActor = CurrentActorInfo->AvatarActor.Get();
    if (!AvatarActor)
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid Avatar Actor"));
        EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
        return;
    }

    AActor* ClosestEnemy = FindClosestEnemy(AvatarActor);
    if(IsValid(ClosestEnemy))
    {
        FVector DirectionToEnemy = (ClosestEnemy->GetActorLocation() - AvatarActor->GetActorLocation()).GetSafeNormal();
        if(IsAutoAimEnabled)
        {
            AvatarActor->SetActorRotation(DirectionToEnemy.Rotation()); // Rotate towards the closest enemy
        }
    }
    
    UAbilityTask_PlayMontageAndWait* PlayMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, FName("None"), CharacterAnimation, 1.0f, FName("None"));  
    if (PlayMontageTask)
    {
        PlayMontageTask->OnCompleted.AddDynamic(this, &UGA_BasicProjectile::OnMontageCompleted);
        PlayMontageTask->ReadyForActivation();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to create PlayMontageAndWait task"));
    }

    UAbilityTask_WaitGameplayEvent* WaitForEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, FGameplayTag::RequestGameplayTag(FName("Event.ProjectileShoot")));
    if (WaitForEventTask)
    {
        WaitForEventTask->EventReceived.AddDynamic(this, &UGA_BasicProjectile::SpawnProjectile);
        WaitForEventTask->ReadyForActivation();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to create WaitGameplayEvent task"));
    }

    UE_LOG(LogTemp, Warning, TEXT("Basic Projectile Ability Activated"));
}

void UGA_BasicProjectile::OnMontageCompleted()
{
    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

AActor* UGA_BasicProjectile::FindClosestEnemy(const AActor* AvatarActor) const
{
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

        if(!Enemy->bHasSpawned)
        {
            // Skip enemies that have not spawned yet
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

    return ClosestEnemy;
}

void UGA_BasicProjectile::SpawnProjectile(FGameplayEventData Payload)
{
    AActor* AvatarActor = CurrentActorInfo->AvatarActor.Get();
    AActor* ClosestEnemy = FindClosestEnemy(AvatarActor);

    FTransform SpawnTransform = AvatarActor->GetTransform();

    //if(IsValid(ClosestEnemy))
    {
        SpawnTransform.SetLocation(AvatarActor->GetActorLocation() + AvatarActor->GetActorForwardVector() * 200.0f); // Adjust spawn location
        SpawnTransform.SetRotation(AvatarActor->GetActorRotation().Quaternion()); // Set rotation to match the character's rotation
    }

    for(int i = 0; i < Number; ++i)
    {
        AActor* SpawnedProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform);
        if(!SpawnedProjectile)
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to spawn projectile"));
            EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
            return;
        }

        // Set the projectile's velocity
        FVector LaunchDirection = AvatarActor->GetActorForwardVector();
        if(IsHomingEnabled)
        {
            LaunchDirection = LaunchDirection.RotateAngleAxis(FMath::RandRange(-90.0f, 90.0f), FVector::UpVector); // Add some random spread
        }
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

            if(IsHomingEnabled && ClosestEnemy)
            {
                ProjectileMovement->HomingTargetComponent = ClosestEnemy->GetRootComponent();
                ProjectileMovement->bIsHomingProjectile = true;
                ProjectileMovement->HomingAccelerationMagnitude = 17500.0f; // Adjust as needed
                ProjectileMovement->bRotationFollowsVelocity = true; // Make the projectile rotate towards the target
            }
        }

        USphereComponent* CollisionComponent = SpawnedProjectile->FindComponentByClass<USphereComponent>();
        if(CollisionComponent)
        {
            CollisionComponent->SetCollisionResponseToChannel(COLLISION_OBJECT_FRIEND, ECR_Ignore);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Projectile does not have a collision component"));
        }
    }

    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

void UGA_BasicProjectile::ShootProjectile(const AActor* AvatarActor, const AActor* ClosestEnemy, float Delay) const
{
   
}