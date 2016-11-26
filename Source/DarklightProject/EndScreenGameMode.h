// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "EndScreenGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DARKLIGHTPROJECT_API AEndScreenGameMode : public AGameMode
{
	GENERATED_BODY()
	void LoadSaves();
public:
	virtual void BeginPlay() override;
	//Ask the player name for the LB
	UFUNCTION(BlueprintImplementableEvent,Category="Leaderboard")
	void SubmitScore(bool isHighscore);
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Leaderboard")
	bool ReceiveName(const FString& Name);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category="Leaderboard")
	UDarklightProjectLeaderboard* LBSave;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Leaderboard")
	UDarklightSaveGame* LastGameSave;
	
};
