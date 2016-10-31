#include "DarklightProject.h"
#include "DarklightProjectCharacter.h"
float ADarklightProjectCharacter::GlobalMaxHealth = 100;
float ADarklightProjectCharacter::GlobalHealth = GlobalMaxHealth;
FPlayerDeath ADarklightProjectCharacter::PlayerDeathEvent;
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
	bSprinting = false;
	MaxSprintSpeed = 1000;
	TrailLenght = 2.4;
	bChargedUp = true;
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<AActor> BombBP(TEXT("/Game/Bombs/MaBombe"));
	if (BombBP.Succeeded())
	{
		CurrentBomb = *BombBP.Class;
	}

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

}


void ADarklightProjectCharacter::BeginPlay()
{
	Super::BeginPlay();
	DefaultMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

float ADarklightProjectCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	GlobalHealth -= ActualDamage;
	if (GlobalHealth <= 0)
	{
		PlayerDeathEvent.Broadcast();
	}
	return ActualDamage;
}

float ADarklightProjectCharacter::GetHealth()
{
	return GlobalHealth;
}

void ADarklightProjectCharacter::SetHealth(float HealthPoints)
{
	GlobalHealth = FMath::Clamp(HealthPoints,0.0f,GlobalMaxHealth);
	if (GlobalHealth <= 0)
	{
		PlayerDeathEvent.Broadcast();
	}
}

float ADarklightProjectCharacter::GetMaxHealth()
{
	return GlobalMaxHealth;
}

void ADarklightProjectCharacter::SetMaxHealth(float HealthPoints)
{
	GlobalMaxHealth = HealthPoints;
}


