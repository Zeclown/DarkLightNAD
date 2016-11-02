// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Plant.h"
#include "GatePlant.generated.h"

/**
 * 
 */
UCLASS()
class DARKLIGHTPROJECT_API AGatePlant : public APlant
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Plant")
	TArray<TSubclassOf<APlant>> Buds;

	
	
	
};
