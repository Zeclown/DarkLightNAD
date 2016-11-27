// Fill out your copyright notice in the Description page of Project Settings.

#include "DarklightProject.h"
#include "Plant.h"


// Sets default values
APlant::APlant()
{
	HitsToActivate = 1;
	PointsOnActivate = 0;
}

// Called when the game starts or when spawned
void APlant::BeginPlay()
{
	Super::BeginPlay();
	HitCounter = HitsToActivate;
	DynamicMaterial = UMaterialInstanceDynamic::Create(ActivatedMaterial, this);
}

bool APlant::Activate_Implementation(ABomb * Activator)
{
	HitCounter--;
	if (HitCounter <= 0 && !bActivated)
	{
		bActivated = true;
		PlantActivatedEvent.Broadcast();
		if (ActivatedMaterial)
		{
			TArray<USkeletalMeshComponent*> Meshes;
			GetComponents<USkeletalMeshComponent>(Meshes);
			for (USkeletalMeshComponent* MeshComps : Meshes)
			{
				MeshComps->SetMaterial(0, ActivatedMaterial);
			}
		}
		ADarklightProjectGameMode* GameMode = Cast<ADarklightProjectGameMode>(GetWorld()->GetAuthGameMode());
		if (GameMode)
			GameMode->IncrementPlayerScore(PointsOnActivate);
		return true;
	}
	return false;
}



