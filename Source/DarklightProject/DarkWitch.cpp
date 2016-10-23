

#include "DarklightProject.h"
#include "DarkWitch.h"
#include "LightWitch.h"
ADarkWitch::ADarkWitch()
{
	PrimaryActorTick.bCanEverTick = true;
	MaxHealth = 100;
}
void ADarkWitch::SetupPlayerInputComponent(UInputComponent * InputComponent)
{
	//////////////////////////////////////////////////////////////////////////
	// Input
	// Set up gameplay key bindings
	/////////////////////////////////////////////////////////////////////////
	InputComponent->BindAction("JumpShadow", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("JumpShadow", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAxis("MoveRightShadow", this, &ADarklightProjectCharacter::MoveRight);
	InputComponent->BindAxis("MoveForwardShadow", this, &ADarklightProjectCharacter::MoveForward);

}

void ADarkWitch::BeginPlay()
{
	Super::BeginPlay();
	//Set the hp for both characters
	GlobalHealth = MaxHealth;
	GlobalMaxHealth = MaxHealth;
}

void ADarkWitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	

}