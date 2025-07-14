// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInteractable.generated.h"
/**
 * 
 */
UINTERFACE(Blueprintable)
class ITTAKESTOQUE_API UInteractable : public UInterface
{
	GENERATED_BODY()
};

class ITTAKESTOQUE_API IInteractable
{
	GENERATED_BODY()
public:
	IInteractable();

	virtual void Interact() = 0;
};
