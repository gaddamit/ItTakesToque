// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGate.h"

#include "NiagaraComponent.h"
#include "ItTakesToque/Character/ItTakesToqueCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelGate::ALevelGate()
{
	IsActivated = false;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root")); // Or use any other component as root

	
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));

	SphereCollision->InitSphereRadius(100.0f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereCollision->SetGenerateOverlapEvents(true);
	SphereCollision->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	GateEffect= CreateDefaultSubobject<UNiagaraComponent>(TEXT("FX"));
	GateEffect->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//GateEffect->SetAutoActivate(false);
	
}

// Called when the game starts or when spawned
void ALevelGate::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(SphereCollision))
	{
		SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ALevelGate::OnOverlapBegin);
	}

	if(IsActivated)
	{
		Activate();
	}
}

// Called every frame
void ALevelGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelGate::Activate()
{
	IsActivated = true;
	if(IsValid(GateEffect))
	{
		GateEffect->Activate();
	}
	OnActivate();
}

void ALevelGate::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!IsActivated)
	{
		return;
	}
	
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		AItTakesToqueCharacter* Character = Cast<AItTakesToqueCharacter>(OtherActor);
		if(IsValid(Character))
		{
			if(Character->CharacterType == ECharacterType::UNDEAD)
			{
				return;
			}
		}
		else
		{
			return;
		}

		SphereCollision->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

		if(LevelNameToLoad != "")
		{
			AGameModeBase* GameMode = GetWorld()->GetAuthGameMode();
			UGameplayStatics::OpenLevel(this, FName(LevelNameToLoad));
		}
	}
}

