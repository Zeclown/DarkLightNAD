// Fill out your copyright notice in the Description page of Project Settings.

#include "DarklightProject.h"
#include "CheckPointPlant.h"

ACheckPointPlant::ACheckPointPlant()
{

}
void ACheckPointPlant::BeginPlay()
{
	//UWorld* GameWorld=GetWorld();
	//for (TObjectIterator<ADarklightProjectGameMode> Itr; Itr; ++Itr)
	//{
	//	// Filter out objects not contained in the target world.
	//	if (Itr->GetWorld() != GameWorld)
	//	{
	//		continue;
	//	}
	//	GM = *Itr;
	//	break;
	//}
}
bool ACheckPointPlant::Activate_Implementation(ABomb * Activator)
{

	return false;
}


