// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelInteractor.h"
#include "../Character/ItTakesToqueCharacter.h"
#include "ItTakesToque/Components/My2AbilitySystemComponent.h"
#include "ItTakesToque/Interfaces/IActivatable.h"
#include "GameplayTagsManager.h"

// Sets default values
ALevelInteractor::ALevelInteractor()
{
	Ability = nullptr;
	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));

	SphereCollision->InitSphereRadius(100.0f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereCollision->SetGenerateOverlapEvents(true);

	InteractUI = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractUI"));
	InteractUI->AttachToComponent(SphereCollision, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ALevelInteractor::BeginPlay()
{
	Super::BeginPlay();
	if(IsValid(SphereCollision))
	{
		SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ALevelInteractor::OnOverlapBegin);
		SphereCollision->OnComponentEndOverlap.AddDynamic(this, &ALevelInteractor::OnOverlapEnd);
	}
	
	InteractUI->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	InteractUI->SetGenerateOverlapEvents(false);
}

// Called every frame
void ALevelInteractor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelInteractor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Level Interactor: OnBeginOverlap"));
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		AItTakesToqueCharacter* Character = Cast<AItTakesToqueCharacter>(OtherActor);
		if(!IsValid(Character) || Character->CharacterType == ECharacterType::UNDEAD)
		{
			return;
		}
		
		if(!InputAction)
		{
			return;
		}

		UMy2AbilitySystemComponent* AbilitySystemComponent = Character->GetAbilitySystemComponent();
		if(AbilitySystemComponent)
		{
			FGameplayAbilitySpecHandle Handle;
			AbilitySystemComponent->FindAbilityFromInputAction(InputAction, Handle);
			FGameplayAbilitySpec* Spec = AbilitySystemComponent->FindAbilitySpecFromHandle(Handle);
			if(Spec)
			{
				Ability = Cast<UGA_Base>(Spec->GetPrimaryInstance());
			}
			
			if(Ability)
			{
				Ability->OnActivateAbility.AddDynamic(this, &ALevelInteractor::Interact);
				const FGameplayTag InteractTag = UGameplayTagsManager::Get().RequestGameplayTag(FName("Event.CanInteract"));
				AbilitySystemComponent->AddLooseGameplayTag(InteractTag);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Level Interactor: No Ability"));
			}
		}
	}
}

void ALevelInteractor::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Level Interactor: OnOverlapEnd"));
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		AItTakesToqueCharacter* Character = Cast<AItTakesToqueCharacter>(OtherActor);
		if(!IsValid(Character) || Character->CharacterType == ECharacterType::UNDEAD)
		{
			return;
		}
		UMy2AbilitySystemComponent* AbilitySystemComponent = Character->GetAbilitySystemComponent();
		if(!AbilitySystemComponent)
		{
			return;
		}
		
		if(Ability)
		{
			Ability->OnActivateAbility.RemoveDynamic(this, &ALevelInteractor::Interact);
			
			const FGameplayTag InteractTag = UGameplayTagsManager::Get().RequestGameplayTag(FName("Event.CanInteract"));
			AbilitySystemComponent->RemoveLooseGameplayTag(InteractTag);
		}
	}
}

void ALevelInteractor::Interact()
{
	for(AActor* Actor : ActorsToActivate)
	{
		if(Actor->Implements<UActivatable>())
		{
			IActivatable* Activatable = Cast<IActivatable>(Actor);
			Activatable->Activate();
		}
	}

	OnInteract();
	UE_LOG(LogTemp, Warning, TEXT("Level Interactor: Interact"));
}

