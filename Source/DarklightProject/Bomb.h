// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS(ABSTRACT)
class DARKLIGHTPROJECT_API ABomb : public AActor
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Bomb Mechanism")
	void Explode();
public:	
	// Sets default values for this actor's properties
	ABomb();

	// Called when the game starts or when spawned
	void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Bomb Mechanism")
	float Radius;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Bomb Mechanism")
	float Damage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Bomb Mechanism", meta = (ClampMin = 0.001f))
	float TimeBeforeExplosion;
	FTimerHandle ExplosionHandle;


	
	
};
