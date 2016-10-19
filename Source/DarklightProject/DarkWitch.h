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
	void Tick(float deltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	void BeginPlay() override;
	//The light counterpart so we can set its inputs

public:
	ADarkWitch();
};
