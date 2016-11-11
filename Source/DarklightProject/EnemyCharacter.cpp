// Fill out your copyright notice in the Description page of Project Settings.

#include "DarklightProject.h"
#include "EnemyCharacter.h"


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{


}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	bDead = false;
	MaxHealthPoint = 60;
	HealthPoint = MaxHealthPoint;
}

float AEnemyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, class AActor * DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	HealthPoint -= ActualDamage;
	if (HealthPoint <= 0)
	{
		bDead = true;
	}
	return ActualDamage;
}

bool AEnemyCharacter::GetBDead() {
	return bDead;
}

