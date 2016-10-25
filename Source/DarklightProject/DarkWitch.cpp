

#include "DarklightProject.h"
#include "DarkWitch.h"
#include "LightWitch.h"
ADarkWitch::ADarkWitch()
{
	MaxHealth = 100;
}

void ADarkWitch::BeginPlay()
{
	Super::BeginPlay();
	//Set the hp for both characters
	GlobalHealth = MaxHealth;
	GlobalMaxHealth = MaxHealth;
}

