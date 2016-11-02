//Owner:Pierre-Olivier Chartrand

#pragma once

#include "Plant.h"
#include "HealingPlant.generated.h"

/**
 * 
 */
UCLASS()
class DARKLIGHTPROJECT_API AHealingPlant : public APlant
{
	GENERATED_BODY()
public:
	AHealingPlant();
	//The amount of healing the plant gives when activated
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float HealingAmount;

	virtual bool Activate_Implementation(ABomb * Activator) override;
	
	
};
