// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "../Constants.h"
#include "../Components/CharacterSwitcher.h"
#include "../Components/CharacterAbilities.h"
#include "../Components/CharacterWeapons.h"
#include "GameplayTagAssetInterface.h"
#include "CharacterAttributeSet.h"
#include "GenericTeamAgentInterface.h"
#include "ItTakesToqueCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UEnhancedInputComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AItTakesToqueCharacter : public ACharacter, public IGameplayTagAssetInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
private:
	UEnhancedInputComponent* InputComponent;
public:
	AItTakesToqueCharacter();
	/** Returns the current character's ability system component. */
	virtual class UMy2AbilitySystemComponent* GetAbilitySystemComponent() const;

	virtual class UCharacterAbilities* GetCharacterAbilities() const;

	virtual class UCharacterWeapons* GetCharacterWeapons() const;

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Abilities")
	void OnAbilitiesSwitched();

	void ChangeCharacterType(ECharacterType Type);
protected:
	void BeginPlay();
	/** Called for movement input */
	void Move(const FInputActionValue& Value);	

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;
	virtual void OnLanded(const FHitResult& Result);
private:
	void BindAbilities();
	void UpdateAbilities();
	void UpdateWeapons();
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	bool bHasSpawned = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	bool bIsAlive = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	ECharacterType CharacterType = ECharacterType::KNIGHT;

	/** Ability System Component **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
    TObjectPtr<UMy2AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UCharacterAbilities> CharacterAbilities;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	TObjectPtr<UCharacterWeapons> CharacterWeapons;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes", meta= (AllowPrivateAccess = "true"))
	const class UCharacterAttributeSet* CharacterAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;

protected:
	FGenericTeamId TeamId;
public:
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }

	UFUNCTION(BlueprintCallable, Category="Character")
	void SetGenericTeamId(const FGenericTeamId& NewTeamID) { TeamId = NewTeamID; }
};

