// Fill out your copyright notice in the Description page of Project Settings.

#include "DarklightProject.h"
#include "HealingPlant.h"
#include "DarklightProjectCharacter.h"

AHealingPlant::AHealingPlant()
{
	HealingAmount = 10;
}
bool AHealingPlant::Activate_Implementation(ABomb * Activator)
{
	if (!bActivated)
	{
		if (Super::Activate_Implementation(Activator))
		{
			ADarklightProjectCharacter::SetHealth(ADarklightProjectCharacter::GetHealth() + HealingAmount);
			return true;
		}
	}
	return false;
}

