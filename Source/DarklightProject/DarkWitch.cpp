

#include "DarklightProject.h"
#include "DarkWitch.h"
#include "LightWitch.h"
#include "Runtime/Engine/Classes/Kismet/KismetMaterialLibrary.h"

ADarkWitch::ADarkWitch()
{
	MaxHealth = 100;
	static ConstructorHelpers::FObjectFinder<UObject> MaterialCol(TEXT("/Game/Characters/Materials/YseraBody"));
	if (MaterialCol.Succeeded())
	{
		BodyMaterialCollection = reinterpret_cast<UMaterialParameterCollection*>(MaterialCol.Object);

	}

}

void ADarkWitch::BeginPlay()
{
	Super::BeginPlay();
	//Set the hp for both characters
	GlobalHealth = MaxHealth;
	GlobalMaxHealth = MaxHealth;
}

