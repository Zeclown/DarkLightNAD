// Fill out your copyright notice in the Description page of Project Settings.

#include "DarklightProject.h"
#include "DarklightProjectGameInstance.h"



void UDarklightProjectGameInstance::Shutdown()
{
	
	//Delete save file
	UDarklightSaveGame* SaveGameInstance = Cast<UDarklightSaveGame>(UGameplayStatics::CreateSaveGameObject(UDarklightSaveGame::StaticClass()));
	UGameplayStatics::DeleteGameInSlot(SaveGameInstance->SaveSlotName, 1);

}
void UDarklightProjectGameInstance::Init()
{
	//Delete save file
	UDarklightSaveGame* SaveGameInstance = Cast<UDarklightSaveGame>(UGameplayStatics::CreateSaveGameObject(UDarklightSaveGame::StaticClass()));
	UGameplayStatics::DeleteGameInSlot(SaveGameInstance->SaveSlotName, 1);
}
