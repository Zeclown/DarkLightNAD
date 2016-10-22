// Fill out your copyright notice in the Description page of Project Settings.

#include "DarklightProject.h"
#include "Bomb.h"


// Sets default values
ABomb::ABomb()
{
	Radius = 10;
	TimeBeforeExplosion = 1;
	Damage = 1;
}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(ExplosionHandle,this,&ABomb::Explode, TimeBeforeExplosion, false, TimeBeforeExplosion);
}



