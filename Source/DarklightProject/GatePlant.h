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
	void BeginPlay() override;
	virtual bool Activate_Implementation(ABomb * Activator) override;
	UFUNCTION()
	void SignalBudActivation();
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Plant")
	TArray<APlant*> Buds;
	int BudsActivated;
	
	
	
};
