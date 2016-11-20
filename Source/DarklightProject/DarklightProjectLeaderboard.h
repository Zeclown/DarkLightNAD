// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DarklightSaveGame.h"
#include "DarklightProjectLeaderboard.generated.h"

/**
 * 
 */
UCLASS()
class DARKLIGHTPROJECT_API UDarklightProjectLeaderboard : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, Category = Leaderboard)
	TMap<FString,int> Scores;
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;
	UDarklightProjectLeaderboard();
};
