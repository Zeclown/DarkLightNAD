//Owner:Pierre-Olivier Chartrand

#pragma once

#include "DarklightProjectCharacter.h"
#include "DarkWitch.generated.h"

/**
 * Class for the shadow clone, takes in the input and send them to LightWitch if necessary
 */
UCLASS()
class DARKLIGHTPROJECT_API ADarkWitch : public ADarklightProjectCharacter
{
	GENERATED_BODY()
protected:
	void BeginPlay() override;

public:
	ADarkWitch();
	//The Maximum HP assigned to both characters at the start for the game
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Player State",meta=(ClampMin=0))
	float MaxHealth;
};
