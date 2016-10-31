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
	HealthPoint = MaxHealthPoint;
}

float AEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	HealthPoint -= ActualDamage;
	if (HealthPoint <= 0)
	{
		bDead = true;
	}
	return ActualDamage;
}





