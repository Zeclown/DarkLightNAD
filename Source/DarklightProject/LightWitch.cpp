#include "DarklightProject.h"
#include "LightWitch.h"

void ALightWitch::BeginPlay()
{
	Super::BeginPlay();
}

ALightWitch::ALightWitch()
{
	PrimaryActorTick.bCanEverTick = true;
}
void ALightWitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
