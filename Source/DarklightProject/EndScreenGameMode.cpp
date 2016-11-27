// Fill out your copyright notice in the Description page of Project Settings.

#include "DarklightProject.h"
#include "EndScreenGameMode.h"

void AEndScreenGameMode::LoadSaves()
{
	//Load both saves
	LastGameSave = Cast<UDarklightSaveGame>(UGameplayStatics::CreateSaveGameObject(UDarklightSaveGame::StaticClass()));
	LastGameSave = Cast<UDarklightSaveGame>(UGameplayStatics::LoadGameFromSlot(LastGameSave->SaveSlotName, 1));

	LBSave = Cast<UDarklightProjectLeaderboard>(UGameplayStatics::CreateSaveGameObject(UDarklightProjectLeaderboard::StaticClass()));
	LBSave = Cast<UDarklightProjectLeaderboard>(UGameplayStatics::LoadGameFromSlot(LBSave->SaveSlotName, 1));
	if (!LBSave)
	{
		LBSave = Cast<UDarklightProjectLeaderboard>(UGameplayStatics::CreateSaveGameObject(UDarklightProjectLeaderboard::StaticClass()));
		UGameplayStatics::SaveGameToSlot(LBSave, LBSave->SaveSlotName, 1);
	}
}

void AEndScreenGameMode::BeginPlay()
{
	Super::BeginPlay();
	LoadSaves();
	//Send the submit score result to the bp
	SubmitScore(LBSave && LBSave->SubmitScore(LastGameSave->PlayerScore));
}

bool AEndScreenGameMode::ReceiveName_Implementation(const FString& Name)
{
	LBSave->AddScore(Name, LastGameSave->PlayerScore);
	UGameplayStatics::SaveGameToSlot(LBSave, LBSave->SaveSlotName, 1);
	return true;
}
