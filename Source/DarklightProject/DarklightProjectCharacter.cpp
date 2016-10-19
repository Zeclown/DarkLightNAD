#include "DarklightProject.h"
#include "DarklightProjectCharacter.h"

ADarklightProjectCharacter::ADarklightProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;
	MaxHealth = 100;
	TrailLenght = 1;
	bChargedUp = true;
	PrimaryActorTick.bCanEverTick = true;
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

}


void ADarklightProjectCharacter::BeginPlay()
{
	Super::BeginPlay();

}
void ADarklightProjectCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	
}
void ADarklightProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADarklightProjectCharacter::MoveForward(float Value)
{
	AddMovementInput(FVector(1.f, 0.f, 0.f), Value);
}

void ADarklightProjectCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f, 1.f, 0.f), Value);
}


