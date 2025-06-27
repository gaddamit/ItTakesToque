
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "../Interfaces/IActivatable.h"
#include "LevelActivator.generated.h"

UCLASS()
class ALevelActivator : public AActor
{
	GENERATED_BODY()
public:
	ALevelActivator();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Default")
	USphereComponent* SphereCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Default")
	TArray<AActor*> ActorsToActivate;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
};
