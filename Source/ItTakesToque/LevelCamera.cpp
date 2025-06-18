#include "LevelCamera.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

ALevelCamera::ALevelCamera()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = true;
    SetActorTickEnabled(true);
}

void ALevelCamera::BeginPlay()
{
    Super::BeginPlay();
    FTimerHandle DelayHandle;
    GetWorldTimerManager().SetTimer(DelayHandle, this, &ALevelCamera::InitializeCamera, 0.1f, false);
}

void ALevelCamera::InitializeCamera()
{
    APlayerController* PlayerController1 = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    APlayerController* PlayerController2 = UGameplayStatics::GetPlayerController(GetWorld(), 1);
    
    PlayerController1->bAutoManageActiveCameraTarget = false;
    PlayerController2->bAutoManageActiveCameraTarget = false;

    if(!PlayerController1 || !PlayerController2)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not found"));
        return;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController found"));
        //PlayerController1->SetViewTargetWithBlend(this, 0.5f);

        Player1 = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        Player2 = UGameplayStatics::GetPlayerCharacter(GetWorld(), 1);

        if(!Player1 || !Player2)
        {
            UE_LOG(LogTemp, Warning, TEXT("Player not found"));
            return;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Player found"));
            PlayerController1->SetViewTargetWithBlend(this, 0.0f);
            PlayerController2->SetViewTargetWithBlend(this, 0.0f);
        }
    }
}

void ALevelCamera::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!IsValid(Player1) && !IsValid(Player2))
    {
        UE_LOG(LogTemp, Warning, TEXT("Players not found"));
        return;
    }

    FVector Player1Location = FVector::ZeroVector;
    FVector Player2Location = FVector::ZeroVector;

    if (IsValid(Player1) && IsValid(Player2))
    {
        Player1Location = Player1->GetActorLocation();
        Player2Location = Player2->GetActorLocation();
    }
    else
    {
        if(!IsValid(Player1))
        {
            APlayerController* PlayerController1 = UGameplayStatics::GetPlayerController(GetWorld(), 0);
            PlayerController1->SetViewTarget(this);
            
            Player1 = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
        }
        if(!IsValid(Player2))
        {
            APlayerController* PlayerController2 = UGameplayStatics::GetPlayerController(GetWorld(), 0);
            Player2 = UGameplayStatics::GetPlayerCharacter(GetWorld(), 1);
        }

        Player1Location = Player2Location = Player1 ? Player1->GetActorLocation(): Player2->GetActorLocation();
    }

    FVector MidPoint = (Player1Location + Player2Location) / 2.0f;
    float Distance = FVector::Distance(Player1Location, Player2Location);

    if(Distance < MinDistanceToAdjust)
    {
        Distance = MinDistanceToAdjust;
    }

    FVector NewCameraLocation = MidPoint + FVector(CameraOffset.X - Distance * CameraZoomXMultiplier, CameraOffset.Y, CameraOffset.Z + Distance * CameraZoomZMultiplier);// + (Distance * CameraZoomMultiplier));
    FVector SmootherCameraLocation = FMath::VInterpTo(GetActorLocation(), NewCameraLocation, DeltaTime, FollowSpeed);
    SetActorLocation(SmootherCameraLocation);
}