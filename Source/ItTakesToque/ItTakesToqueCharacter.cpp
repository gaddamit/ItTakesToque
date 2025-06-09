// Copyright Epic Games, Inc. All Rights Reserved.

#include "ItTakesToqueCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/My2AbilitySystemComponent.h"
#include "CharacterAttributeSet.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AItTakesToqueCharacter

AItTakesToqueCharacter::AItTakesToqueCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CharacterAttributeSet = CreateDefaultSubobject<UCharacterAttributeSet>(TEXT("CharacterAttributeSet"));
	UE_LOG(LogTemplateCharacter, Log, TEXT("Character Attribute Set created for %s"), *GetNameSafe(this));
}


UMy2AbilitySystemComponent* AItTakesToqueCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UCharacterAbilities* AItTakesToqueCharacter::GetCharacterAbilities() const
{
	return CharacterAbilities;
}

UCharacterWeapons* AItTakesToqueCharacter::GetCharacterWeapons() const
{
	return CharacterWeapons;
}

void AItTakesToqueCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	UE_LOG(LogTemplateCharacter, Log, TEXT("BeginPlay for %s"), *GetNameSafe(this));
}

void AItTakesToqueCharacter::BindAbilities()
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Binding abilities for %s"), *GetNameSafe(this));
	if(AbilitySystemComponent && CharacterAbilities)
	{
		TMap<TObjectPtr<UInputAction>, TSubclassOf<UGameplayAbility>>& Abilities = CharacterAbilities->Abilities;
		// Iterate through the map and bind each ability to the corresponding input action
		for (const TPair<TObjectPtr<UInputAction>, TSubclassOf<UGameplayAbility>>& Pair : Abilities)
		{
			TObjectPtr<UInputAction> InputAction = Pair.Key;
			TSubclassOf<UGameplayAbility> Ability = Pair.Value;

			if (InputAction && Ability)
			{
				// Save handle from give ability
				FGameplayAbilitySpecHandle AbilityHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, static_cast<int32>(EAbilityInputID::None), this));
				AbilitySystemComponent->SetInputBinding(InputAction, AbilityHandle);
			}
			else
			{
				UE_LOG(LogTemplateCharacter, Warning, TEXT("Invalid Input Action or Ability for %s"), *GetNameSafe(this));
			}
		}
	}
}

void AItTakesToqueCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AItTakesToqueCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	UE_LOG(LogTemplateCharacter, Log, TEXT("PostInitializeComponents for %s"), *GetNameSafe(this));

	// Initialize the Ability System Component
	UpdateAbilities();
	// Initialize the Weapon Component
	UpdateWeapons();
}

void AItTakesToqueCharacter::UpdateAbilities()
{

	UObject* ASC = FindComponentByClass<UMy2AbilitySystemComponent>();
	if(ASC)
	{
		AbilitySystemComponent = Cast<UMy2AbilitySystemComponent>(ASC);
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		UE_LOG(LogTemplateCharacter, Log, TEXT("Found an Ability System Component in %s"), *GetNameSafe(this));
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("Failed to find an Ability System Component in %s"), *GetNameSafe(this));
	}

	if(IsValid(AbilitySystemComponent))
	{
		// Register the Character Attribute Set
		CharacterAttributeSet = AbilitySystemComponent->GetSet<UCharacterAttributeSet>();
		if (CharacterAttributeSet)
		{
			if(DefaultAttributeEffect)
			{
				// Apply the default attribute effect to the character
				FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
				EffectContext.AddSourceObject(this);
				FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributeEffect, 1, EffectContext);
				if (SpecHandle.IsValid())
				{
					AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
					UE_LOG(LogTemplateCharacter, Log, TEXT("Applied Default Attribute Effect to %s"), *GetNameSafe(this));
				}
			}
			else
			{
				UE_LOG(LogTemplateCharacter, Error, TEXT("Default Attribute Effect is not set!"));
			}
		}
		else
		{
			UE_LOG(LogTemplateCharacter, Error, TEXT("Failed to initialize Character Attribute Set!"));
		}
	}
}

void AItTakesToqueCharacter::UpdateWeapons()
{
	UObject* Weapons = FindComponentByClass<UCharacterWeapons>();
	if(Weapons)
	{
		CharacterWeapons = Cast<UCharacterWeapons>(Weapons);
		UE_LOG(LogTemplateCharacter, Log, TEXT("Found a Character Weapons component in %s"), *GetNameSafe(this));
		CharacterWeapons->UpdateWeapons(this);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("Failed to find a Character Weapons component in %s"), *GetNameSafe(this));
	}
}

void AItTakesToqueCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UE_LOG(LogTemplateCharacter, Log, TEXT("Setting up player input component for %s"), *GetNameSafe(this));
	// Set up action bindings
	InputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (InputComponent) {
		// Moving
		InputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AItTakesToqueCharacter::Move);
		
		if(IsValid(AbilitySystemComponent))
		{
			AbilitySystemComponent->SetInputComponent(InputComponent);
		}
		else
		{
			UE_LOG(LogTemplateCharacter, Error, TEXT("Failed to find an Ability System Component!"));
		}

		UObject* Abilities = FindComponentByClass<UCharacterAbilities>();
		if (Abilities)
		{
			CharacterAbilities = Cast<UCharacterAbilities>(Abilities);
		}
		else
		{
			UE_LOG(LogTemplateCharacter, Error, TEXT("Failed to find a Character Abilities component!"));
		}

		BindAbilities();
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AItTakesToqueCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AItTakesToqueCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AItTakesToqueCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->GetOwnedGameplayTags(TagContainer);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Warning, TEXT("AbilitySystemComponent is null in %s"), *GetNameSafe(this));	
	}
}