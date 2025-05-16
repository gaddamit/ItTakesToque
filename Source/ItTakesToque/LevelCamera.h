// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "GameFramework/Character.h"
#include "LevelCamera.generated.h"

/**
 * 
 */
UCLASS()
class ITTAKESTOQUE_API ALevelCamera : public ACameraActor
{
	GENERATED_BODY()
	public:
		ALevelCamera();
	protected:
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;

	private:
		void InitializeCamera();
		UPROPERTY(EditAnywhere);
		float CameraHeight = 800.0f;

		UPROPERTY(EditAnywhere);
		float CameraZoomMultiplier = 0.5f;

		UPROPERTY(EditAnywhere);
		float FollowSpeed = 5.0f;

		UPROPERTY(EditAnywhere);
		FVector CameraOffset = FVector(-1500.0f, 0.0f, 800.0f);

		UPROPERTY(EditAnywhere);
		ACharacter* Player1;
		UPROPERTY(EditAnywhere);
		ACharacter* Player2;
};
