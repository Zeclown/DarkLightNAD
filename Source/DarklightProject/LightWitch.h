//Owner:Pierre-Olivier Chartrand

#pragma once

#include "DarklightProjectCharacter.h"
#include "LightWitch.generated.h"

/**
 * 
 */
UCLASS()
class DARKLIGHTPROJECT_API ALightWitch : public ADarklightProjectCharacter
{
	GENERATED_BODY()
	
protected:
	/**Tick event called by the blueprint */
	void Tick(float DeltaTime) override;
	void BeginPlay() override;
public:
	ALightWitch();
	
	
};
