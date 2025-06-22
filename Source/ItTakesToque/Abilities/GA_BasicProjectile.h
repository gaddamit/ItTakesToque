// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_Base.h"
#include "GA_BasicProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ITTAKESTOQUE_API UGA_BasicProjectile : public UGA_Base
{
	GENERATED_BODY()
public:
	UGA_BasicProjectile();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<class AActor> ProjectileClass; // The class of the projectile to spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ProjectileSpeed = 3000.0f; // Speed of the projectile
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ProjectileLifetime = 5.0f; // Lifetime of the projectile in seconds

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	int Number = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	bool IsAutoAimEnabled = true; // Whether auto-aim is enabled for the projectile)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	bool IsHomingEnabled = false; // Whether homing is enabled for the projectile)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	UAnimMontage* CharacterAnimation; // Animation to play when the projectile is spawned
	UFUNCTION(BlueprintImplementableEvent, Category = "MyEvents")
    void OnAbilityActivated(FTransform SpawnTransform);

	UFUNCTION(BlueprintCallable, Category = "MyEvents")
	void OnMontageCompleted();
	UFUNCTION(BlueprintCallable, Category = "MyEvents")
	void SpawnProjectile(FGameplayEventData Payload);

private:
	FTransform SpawnTransform;
	FVector LaunchDirection;
private:
	AActor* FindClosestEnemy(const AActor* AvatarActor) const;
	void ShootProjectile(const AActor* AvatarActor, const AActor* ClosestEnemy, float Delay) const;
};
