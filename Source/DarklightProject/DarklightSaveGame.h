// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "DarklightSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class DARKLIGHTPROJECT_API UDarklightSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString LevelName;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	int PlayerScore;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString CheckPointID;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;
	UPROPERTY(VisibleAnywhere, Category = Plants)
	TMap<FString,bool> Activated;

	UDarklightSaveGame();
	
};
