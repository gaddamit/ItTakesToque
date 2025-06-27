// Copyright Epic Games, Inc. All Rights Reserved.

#include "ItTakesToqueGameMode.h"
#include "Character/ItTakesToqueCharacter.h"
#include "UObject/ConstructorHelpers.h"

AItTakesToqueGameMode::AItTakesToqueGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
