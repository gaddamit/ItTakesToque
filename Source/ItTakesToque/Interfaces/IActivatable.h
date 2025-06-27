// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IActivatable.generated.h"
/**
 * 
 */
UINTERFACE(Blueprintable)
class ITTAKESTOQUE_API UActivatable : public UInterface
{
	GENERATED_BODY()
};

class ITTAKESTOQUE_API IActivatable
{
	GENERATED_BODY()
public:
	IActivatable();

	virtual void Activate() = 0;
};
