// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "DarklightProjectGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DARKLIGHTPROJECT_API UDarklightProjectGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
		void Shutdown() override;
		void Init() override;
	
};
