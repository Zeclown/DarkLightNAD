//Owner:Pierre-Olivier Chartrand
// Base class for plants that interacts with the players

#pragma once

#include "GameFramework/Actor.h"
#include "ActivableInterface.h"
#include "Plant.generated.h"
DECLARE_EVENT(APlant, FPlantActivated);
UCLASS(ABSTRACT)
class DARKLIGHTPROJECT_API APlant : public AActor,public IActivableInterface
{
	GENERATED_BODY()
protected:
	FPlantActivated PlantActivatedEvent;
	//The number of explosion that hit this plant
	int HitCounter;
public:	
	// Sets default values for this actor's properties
	APlant();
	// Called when the game starts or when spawned
	 void BeginPlay() override;
	 virtual bool Activate_Implementation(ABomb * Activator) override;
	 //Is the plant already activated
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plant")
	bool bActivated;
	 //The number of explosions required to activate this plant
	 UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plant",meta= (ClampMin = 1))
	int HitsToActivate;
	 FPlantActivated& OnPlantActivate() { return PlantActivatedEvent; }

};
