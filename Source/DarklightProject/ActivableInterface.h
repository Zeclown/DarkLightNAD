// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Bomb.h"
#include "ActivableInterface.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
class DARKLIGHTPROJECT_API UActivableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};
class DARKLIGHTPROJECT_API IActivableInterface {
	GENERATED_IINTERFACE_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Activable")
	bool Activate(ABomb* Activator);

};