// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DarklightSaveGame.h"
#include "DarklightProjectLeaderboard.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FLeaderboardEntry
{
	GENERATED_BODY()
public:
	FLeaderboardEntry()
	{};
	FLeaderboardEntry(FString Name, int Score)
		:Name(Name),Score(Score)
	{
	};
	UPROPERTY(BlueprintReadOnly)
	FString Name;
	UPROPERTY(BlueprintReadOnly)
	int Score;
};
UCLASS()
class DARKLIGHTPROJECT_API UDarklightProjectLeaderboard : public USaveGame
{
	GENERATED_BODY()

protected:
	const int MAX_NUMBER_OF_ENTRIES = 10;
	UFUNCTION(Category = Leaderboard)
	void OrderScores();
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Leaderboard)
	TArray<FLeaderboardEntry> ScoreEntries;
public:
	UDarklightProjectLeaderboard();
	UPROPERTY(VisibleAnywhere, Category = Basic)
	FString SaveSlotName;
	//Returns whether the score is a new highscore or not
	UFUNCTION(Category = Leaderboard)
	bool SubmitScore(int Score);
	//Add a new score to the leaderboard (Always check the result of SubmitScore() beforehand)
	UFUNCTION(Category = Leaderboard)
	void AddScore(FString Name, int Score);

};
