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
#include "Abilities/GA_Fireball.h"

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

	//Initialize the Ability System Component
	AbilitySystemComponent = CreateDefaultSubobject<UMy2AbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

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

void AItTakesToqueCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Dash
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &AItTakesToqueCharacter::Dash);
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Completed, this, &AItTakesToqueCharacter::StopDash);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AItTakesToqueCharacter::Interact);

		// Cancel
		EnhancedInputComponent->BindAction(CancelAction, ETriggerEvent::Started, this, &AItTakesToqueCharacter::Cancel);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AItTakesToqueCharacter::Move);

		// Looking
		//EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AItTakesToqueCharacter::Look);

		// Skills
		EnhancedInputComponent->BindAction(Skill1Action, ETriggerEvent::Started, this, &AItTakesToqueCharacter::Skill1);
		EnhancedInputComponent->BindAction(Skill2Action, ETriggerEvent::Started, this, &AItTakesToqueCharacter::Skill2);
		EnhancedInputComponent->BindAction(Skill3Action, ETriggerEvent::Started, this, &AItTakesToqueCharacter::Skill3);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AItTakesToqueCharacter::Dash()
{
	// Implement dash logic here
	UE_LOG(LogTemplateCharacter, Log, TEXT("Dash pressed"));
}

void AItTakesToqueCharacter::StopDash()
{
	// Implement stop dash logic here
	UE_LOG(LogTemplateCharacter, Log, TEXT("Dash released"));
}

void AItTakesToqueCharacter::Interact()
{
	// Implement interact logic here
	UE_LOG(LogTemplateCharacter, Log, TEXT("Interact pressed"));
}

void AItTakesToqueCharacter::Cancel()
{
	// Implement cancel logic here
	UE_LOG(LogTemplateCharacter, Log, TEXT("Cancel pressed"));
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

void AItTakesToqueCharacter::Skill1()
{
	// Implement skill 1 logic here
	UE_LOG(LogTemplateCharacter, Log, TEXT("Skill 1 pressed"));
}
void AItTakesToqueCharacter::Skill2()
{
	// Implement skill 2 logic here
	UE_LOG(LogTemplateCharacter, Log, TEXT("Skill 2 pressed"));
}
void AItTakesToqueCharacter::Skill3()
{
	// Implement skill 3 logic here
	UE_LOG(LogTemplateCharacter, Log, TEXT("Skill 3 pressed"));
}