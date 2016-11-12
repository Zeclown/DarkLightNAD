#include "DarklightProject.h"
#include "LightWitch.h"
#include "Runtime/Engine/Classes/Kismet/KismetMaterialLibrary.h"
ALightWitch::ALightWitch()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UObject> MaterialCol(TEXT("/Game/Characters/Materials/RoxyBody"));
	if (MaterialCol.Succeeded())
	{
		BodyMaterialCollection = reinterpret_cast<UMaterialParameterCollection*>(MaterialCol.Object);

	}
	GetMesh()->CustomDepthStencilValue = STENCIL_ROXY_OUTLINE;
}
void ALightWitch::BeginPlay()
{
	Super::BeginPlay();

}


void ALightWitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
