// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAbilities.h"
#include "../ItTakesToqueCharacter.h"
#include "My2AbilitySystemComponent.h"

// Sets default values for this component's properties
UCharacterAbilities::UCharacterAbilities()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterAbilities::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCharacterAbilities::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCharacterAbilities::OnCollect(AActor* Collector)
{
    Super::OnCollect(Collector);
    // Implement the logic for switching characters
    // For example, you might want to change the player's character or update the game state

	AItTakesToqueCharacter* PlayerCharacter = Cast<AItTakesToqueCharacter>(Collector);
    if(!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Collector is not a valid player character"));
		return;
	}

	UMy2AbilitySystemComponent* ASC = PlayerCharacter->GetAbilitySystemComponent();
	if(!ASC)
	{
		UE_LOG(LogTemp, Warning, TEXT("Collector is not a valid player character"));
		return;
	}

	UCharacterAbilities* CA = PlayerCharacter->GetCharacterAbilities();
	if(!CA)
	{
		UE_LOG(LogTemp, Warning, TEXT("Collector is not a valid player character"));
		return;
	}

	for (const auto& AbilityPair : Abilities)
	{
		UInputAction* InputAction = AbilityPair.Key;
		TSubclassOf<UGameplayAbility> Ability = AbilityPair.Value;

		if (InputAction && Ability)
		{
			ASC->ClearAbilityBindings(InputAction); // Clear any existing bindings for this input action
			// Give the ability to the Ability System Component
			FGameplayAbilitySpecHandle AbilityHandle = ASC->GiveAbility(FGameplayAbilitySpec(Ability, 1, INDEX_NONE, PlayerCharacter));
			// Bind the ability to the input action
			ASC->SetInputBinding(InputAction, AbilityHandle);
			// Log the binding for debugging purposes
			UE_LOG(LogTemp, Warning, TEXT("Bound ability %s to input action %s"), *GetNameSafe(Ability), *GetNameSafe(InputAction));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid Input Action or Ability for %s"), *GetNameSafe(this));
		}
	}
}
