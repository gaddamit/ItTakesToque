#include "LevelActivator.h"

#include "ItTakesToque/Character/ItTakesToqueCharacter.h"

ALevelActivator::ALevelActivator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));

	SphereCollision->InitSphereRadius(100.0f);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	SphereCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SphereCollision->SetGenerateOverlapEvents(true);
}

void ALevelActivator::BeginPlay()
{
	if(IsValid(SphereCollision))
	{
		SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ALevelActivator::OnOverlapBegin);
	}
}

void ALevelActivator::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Level Activator: OnBeginOverlap"));
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
		
		for (auto Element : ActorsToActivate)
		{
			if(IsValid(Element) && Element->Implements<UActivatable>())
			{
				IActivatable* Activatable = Cast<IActivatable>(Element);
				Activatable->Activate();
			}
		}

		SphereCollision->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	}
}
