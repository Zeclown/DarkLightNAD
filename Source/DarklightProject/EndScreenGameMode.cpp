// Fill out your copyright notice in the Description page of Project Settings.

#include "DarklightProject.h"
#include "EndScreenGameMode.h"

void AEndScreenGameMode::LoadSaves()
{

	//Load both saves
	LastGameSave = Cast<UDarklightSaveGame>(UGameplayStatics::CreateSaveGameObject(UDarklightSaveGame::StaticClass()));
	LastGameSave = Cast<UDarklightSaveGame>(UGameplayStatics::LoadGameFromSlot(LastGameSave->SaveSlotName, 1));
	switch (LastGameSave->GameMode)
	{
	case 1:
		LBName = "Race Leaderboard";
		break;
	case 2:
		LBName = "Survival Leaderboard";
		break;
	default:
		LBName= "Story Leaderboard";
	}
	LBSave = Cast<UDarklightProjectLeaderboard>(UGameplayStatics::LoadGameFromSlot(LBName, 1));
	if (!LBSave)
	{
		LBSave = Cast<UDarklightProjectLeaderboard>(UGameplayStatics::CreateSaveGameObject(UDarklightProjectLeaderboard::StaticClass()));
		UGameplayStatics::SaveGameToSlot(LBSave, LBName, 1);
	}
}

void AEndScreenGameMode::BeginPlay()
{
	Super::BeginPlay();
	LoadSaves();
	//Send the submit score result to the bp
	SubmitScore(LBSave && LBSave->SubmitScore(LastGameSave->PlayerScore));
}

void AEndScreenGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	//Assure destruction of last checkpoint for next Gameplay loop
	UGameplayStatics::DeleteGameInSlot(LastGameSave->SaveSlotName, 1);
}

bool AEndScreenGameMode::ReceiveName_Implementation(const FString& Name)
{
	LBSave->AddScore(Name, LastGameSave->PlayerScore);
	UGameplayStatics::SaveGameToSlot(LBSave, LBName, 1);
	return true;
}
