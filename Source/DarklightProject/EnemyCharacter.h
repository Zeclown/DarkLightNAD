// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class DARKLIGHTPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()
	bool bDead;
public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//The number of hp this unit currently has
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float HealthPoint;
	//The maximum number of hp for this unit
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="State")
	float MaxHealthPoint;
	UFUNCTION(BlueprintCallable, Category = "State")
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;


	
	
};
