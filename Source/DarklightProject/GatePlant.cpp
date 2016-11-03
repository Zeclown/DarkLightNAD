// Fill out your copyright notice in the Description page of Project Settings.

#include "DarklightProject.h"
#include "GatePlant.h"
void AGatePlant::BeginPlay()
{
	BudsActivated = 0;
	for (APlant* Bud : Buds)
	{
		if (Bud->bActivated)
		{
			BudsActivated++;
		}
		Bud->OnPlantActivate().AddUObject(this,&AGatePlant::SignalBudActivation);

	}
}
void AGatePlant::SignalBudActivation()
{
	BudsActivated++;
	if (BudsActivated >= Buds.Num())
	{
		Activate_Implementation(nullptr);
	}
}



