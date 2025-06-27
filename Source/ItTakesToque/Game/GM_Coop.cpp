// Fill out your copyright notice in the Description page of Project Settings.


#include "GM_Coop.h"

AGM_Coop::AGM_Coop()
{
    // Set this game mode to be the default for the project
    DefaultPawnClass = nullptr; // Set to your custom pawn class if needed
    PlayerControllerClass = nullptr; // Set to your custom player controller class if needed
    HUDClass = nullptr; // Set to your custom HUD class if needed\
    // Additional initialization can be done here
}

void AGM_Coop::BeginPlay()
{
    Super::BeginPlay();
    
    // Initialize any game mode specific logic here
    UE_LOG(LogTemp, Warning, TEXT("Co-op Game Mode has started!"));
    
    // You can set up player spawning, rules, etc. here
}