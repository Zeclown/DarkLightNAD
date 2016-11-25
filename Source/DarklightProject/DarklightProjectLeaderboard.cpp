// Fill out your copyright notice in the Description page of Project Settings.

#include "DarklightProject.h"
#include "DarklightProjectLeaderboard.h"



void UDarklightProjectLeaderboard::OrderScores()
{
	for (int i = 0; i < ScoreEntries.Num()-1; i++)
	{
		if (ScoreEntries[i].Score > ScoreEntries[i + 1].Score)
		{
			ScoreEntries.Swap(i, i + 1);
			i = 0;
		}
	}
}
bool UDarklightProjectLeaderboard::SubmitScore(int Score)
{
	return ScoreEntries.Num() < MAX_NUMBER_OF_ENTRIES || Score < ScoreEntries.Last().Score;
}
void UDarklightProjectLeaderboard::AddScore(FString Name, int Score)
{
	if (ScoreEntries.Num() < MAX_NUMBER_OF_ENTRIES)
		ScoreEntries.Add(FLeaderboardEntry(Name, Score));
	else
		ScoreEntries[ScoreEntries.Num() - 1] = FLeaderboardEntry(Name, Score);
	OrderScores();
}

UDarklightProjectLeaderboard::UDarklightProjectLeaderboard()
{
	SaveSlotName = TEXT("Leaderboard");
	OrderScores();
}