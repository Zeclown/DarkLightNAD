// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "DarklightProjectCharacter.h"
#include "DarklightProjectGameMode.generated.h"
UCLASS(ABSTRACT)
class ADarklightProjectGameMode : public AGameMode
{
	GENERATED_BODY()
protected:
	void CheckTrailCollisions();
	//The position of the players saved
	TArray<TArray<FVector>> SavedPoints;
	FTimerHandle TrailCheckTimer;
	TArray<ADarklightProjectCharacter*> Players;
	TArray<float> PlayersTrailTimers;


public:
	ADarklightProjectGameMode();
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintImplementableEvent, Category = "Trail Algorythm")
	void HandleTrailCollision(FVector ContactPoint);
	/** How many time passes between trail collision checks in seconds. Shorter time means collision detection is more accurate but also more costly */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Optimisation")
	float TrailQueryRate;
	/** When doing collision check, how many segment should we be skipping per check. e.g.: 0.5 will mean every two checks, one segment will be passed.
	Smaller numbers means collision detection is more accurate but also more costly */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Optimisation")
	float SegmentsToSkip;
	/** The maximum distance where two trails are considered to be intersecting*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trail Algorythm")
	float TrailDistanceTolerance;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trail Algorythm")
	bool bDebugTrail;

};



