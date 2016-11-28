// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyCharacter.h"
#include "BirdBossCharacter.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EBirdBossState : uint8 
{
BS_IDLE UMETA(DisplayName = "Idle"),
BS_IDLECOMBAT UMETA(DisplayName = "Idle Combat"),
BS_PECK UMETA(DisplayName = "Peck"),
BS_DEAD UMETA(DisplayName = "Dead"),
BS_WINDBLAST UMETA(DisplayName = "Windblast"),
BS_SPAWNBUGS UMETA(DisplayName = "SpawnBugs")
};
UCLASS()
class DARKLIGHTPROJECT_API ABirdBossCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = State)
	EBirdBossState MainState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack - Peck")
	float PeckRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack - Peck")
	int PeckDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack - Peck")
	FVector PeckOffset;
};
