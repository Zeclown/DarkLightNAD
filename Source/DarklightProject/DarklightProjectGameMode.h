// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "DarklightProjectCharacter.h"
#include "DarklightProjectGameMode.generated.h"
USTRUCT(BlueprintType)
struct FComboLevel
{
	GENERATED_BODY()
public:
	//Minimum number of combo points to have before reaching this Combo Level
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo Stats")
	int MinimumComboPoints;
	/*
	% increase of power for that Combo Level. 
	Note that the % is cumulative with the lower combo levels.E.g. 10 (base damage) + 5 (50 % bonus phase 1) + 15(100 % bonus phase 2) = 30
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combo Stats")
	float ComboModifier;
};

UCLASS(ABSTRACT)
class DARKLIGHTPROJECT_API ADarklightProjectGameMode : public AGameMode
{
	GENERATED_BODY()
protected:
	void CheckTrailCollisions();
	//The position of the players saved
	TArray<TArray<FVector>> SavedPoints;
	//The handle of the timer for trail collision checking
	FTimerHandle TrailCheckTimer;
	//The handle of the timer for combo checking
	FTimerHandle ComboCheckTimer;

	TArray<ADarklightProjectCharacter*> Players;
	TArray<float> PlayersTrailTimers;
	//The number of combo points (Consecutive bombs created)
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Combo Mechanic")
	int CurrentComboPoints;
	//The current combo level
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Combo Mechanic")
	int ComboStageIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combo Mechanic")
	float ActiveComboModifier;
	//The number of bomb currently in game
	int BombCount;

public:
	ADarklightProjectGameMode();
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintNativeEvent, Category = "Trail Algorythm")
	void HandleTrailCollision(FVector ContactPoint,ADarklightProjectCharacter* Bomber);
	//Function called by timer that reset the combo level and points of the player
	void ResetCombo();
	//Function called when a bomb is destroyed (so we can track the number of bomb currently in game)
	UFUNCTION()
	void SignalBombDestruction(AActor* DestroyedBomb);
	//Function called when a combo point is added which check if we are at a new combo level
	void AddComboPoint();
	/** How many time passes between trail collision checks in seconds. Shorter time means collision detection is more accurate but also more costly */
	UPROPERTY(EditDefaultsOnly, Category = "Optimisation")
	float TrailQueryRate;
	//The maximum duration between bombs without losing your combo, negative time mean it is based on the bomb duration (Combo as long as another bomb is still there) 
	UPROPERTY(EditDefaultsOnly, Category = "Combo Mechanic")
	float ComboTimeWindow;
	//Every combo stages in < order
	UPROPERTY(EditDefaultsOnly, Category = "Combo Mechanic")
	TArray<FComboLevel> ComboStages;
	/** When doing collision check, how many segment should we be skipping per check. e.g.: 0.5 will mean every two checks, one segment will be passed.
	Smaller numbers means collision detection is more accurate but also more costly */
	UPROPERTY(EditDefaultsOnly, Category = "Optimisation")
	float SegmentsToSkip;
	/** The maximum distance where two trails are considered to be intersecting*/
	UPROPERTY(EditDefaultsOnly, Category = "Trail Algorythm")
	float TrailDistanceTolerance;
	UPROPERTY(EditDefaultsOnly, Category = "Trail Algorythm")
	bool bDebugTrail;
	UPROPERTY(EditDefaultsOnly, Category = "Trail Algorythm")
	bool bDebugCombo;
};



