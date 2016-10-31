// Fill out your copyright notice in the Description page of Project Settings.

#include "DarklightProject.h"
#include "Bomb.h"


// Sets default values
ABomb::ABomb()
{
	Radius = 100;
	TimeBeforeExplosion = 1;
	BaseDamage = 100;
	MinDamage = 30;
	DamageInnerRadius = 30;
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(ExplosionHandle,this,&ABomb::Explode, TimeBeforeExplosion, false, TimeBeforeExplosion);
}



