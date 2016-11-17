// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Plant.h"
#include "CheckPointPlant.generated.h"

/**
 * 
 */
UCLASS()
class DARKLIGHTPROJECT_API ACheckPointPlant : public APlant
{
	GENERATED_BODY()
protected:
	ADarklightProjectGameMode* GM;
public:
	ACheckPointPlant();
	virtual bool Activate_Implementation(ABomb * Activator) override;
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> SpawnPoints;
	
};
