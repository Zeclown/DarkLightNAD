// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ActivableActor.generated.h"

UCLASS(ABSTRACT)
class DARKLIGHTPROJECT_API AActivableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActivableActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	//Function called by bomb explosions and other interactions
	virtual void Activate() PURE_VIRTUAL(AActivableActor::Activate,);

	
	
};
