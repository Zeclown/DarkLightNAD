// Fill out your copyright notice in the Description page of Project Settings.

#include "DarklightProject.h"
#include "Plant.h"


// Sets default values
APlant::APlant()
{
	HitsToActivate = 1;
}

// Called when the game starts or when spawned
void APlant::BeginPlay()
{
	Super::BeginPlay();
	
}

bool APlant::Activate_Implementation(ABomb * Activator)
{
	bActivated = true;
	PlantActivatedEvent.Broadcast();
	return true;
}



