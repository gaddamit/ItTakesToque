// Fill out your copyright notice in the Description page of Project Settings.


#include "GI_GameInstance.h"

UGI_GameInstance::UGI_GameInstance()
{
	
}

ECharacterType UGI_GameInstance::GetCharacterType(int Player) const
{
	return Player == 0 ? CharacterType1 : CharacterType2;
}


void UGI_GameInstance::SetCharacterType(int Player, ECharacterType Type)
{
	UE_LOG(LogTemp, Warning, TEXT("Change Player %d to Character %d."), Player, int(Type));
	if(Player == 0)
	{
		CharacterType1 = Type;
	}
	else
	{
		CharacterType2 = Type;
	}
}

void UGI_GameInstance::PrintCharacterType() const
{
	UE_LOG(LogTemp, Warning, TEXT("Player1: Character %d."),CharacterType1);
	UE_LOG(LogTemp, Warning, TEXT("Player2: Character %d."),CharacterType1);
}

