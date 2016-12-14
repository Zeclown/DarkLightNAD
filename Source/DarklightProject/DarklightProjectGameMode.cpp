// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "DarklightProject.h"
#include "DarklightProjectGameMode.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"
#include "Engine/Blueprint.h"
#include "DarklightProject/Bomb.h"
#include "CheckPointPlant.h"
#include "GameStateSaver.h"
ADarklightProjectGameMode::ADarklightProjectGameMode()
{
	TrailQueryRate = 0.05f;
	SegmentsToSkip = 0;
	TrailDistanceTolerance = 20;
	bDebugTrail = false;
	FComboLevel MinimumLevel = FComboLevel();
	MinimumLevel.ComboModifier = 0;
	MinimumLevel.MinimumComboPoints = 0;
	ComboStages.Add(MinimumLevel);
	MinimumBombDistance = 15;
}
void ADarklightProjectGameMode::BeginPlay()
{
	Super::BeginPlay();
	bFirstLoad = true;
	ComboStageIndex = 0;
	CurrentComboPoints = 0;
	PlayerScore = 0;
	ChallengeType = EGameChallengeType::GC_STORY;
	LastCheckPoint = nullptr;
	//Set Timer for  trail collision check
	GetWorld()->GetTimerManager().SetTimer(TrailCheckTimer, this, &ADarklightProjectGameMode::CheckTrailCollisions, TrailQueryRate, true);
	//Subscribe to the player death event
	ADarklightProjectCharacter::OnDeath().AddUObject(this, &ADarklightProjectGameMode::HandlePlayerDeath);
	//Find players in game
	for (TObjectIterator<ADarklightProjectCharacter> Itr; Itr; ++Itr)
	{
		if (Itr->GetWorld() != GetWorld())
		{
			continue;
		}
		Players.Add(*Itr);
		SavedPoints.Add(TArray<FTrailPoint>());
	}
	LoadSave();
	OnGameLoaded();
}

void ADarklightProjectGameMode::EndGame_Implementation()
{
	SaveGame();
	UGameplayStatics::OpenLevel(GetWorld(), "EndMenuLevel");
}



void ADarklightProjectGameMode::HandlePlayerDeath_Implementation()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}



void ADarklightProjectGameMode::SaveCheckpoint_Implementation( ACheckPointPlant * CheckPoint)
{
	LastCheckPoint = CheckPoint;
	GameStateSaver::SaveInit(GetWorld(), CheckPoint, GetWorld()->StreamingLevelsPrefix, PlayerScore,ChallengeType);
}

void ADarklightProjectGameMode::SaveGame()
{
	SaveCheckpoint_Implementation(LastCheckPoint);
}

void ADarklightProjectGameMode::LoadSave()
{
	while (IsSaving())
	{

	}
	UDarklightSaveGame* LoadGameInstance = Cast<UDarklightSaveGame>(UGameplayStatics::CreateSaveGameObject(UDarklightSaveGame::StaticClass()));
	LoadGameInstance = Cast<UDarklightSaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, 1));
	if (LoadGameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("Save File detected"), );
		bFirstLoad = false;
		PlayerScore = LoadGameInstance->PlayerScore;
		//Get all the plants currently in the level
		TArray<APlant*> LevelPlants;
		for (TObjectIterator<APlant> Itr; Itr; ++Itr)
		{
			if (Itr->GetWorld() != GetWorld())
			{
				continue;
			}
			LevelPlants.Add(*Itr);
		}
		for (auto PlantSaved : LoadGameInstance->Activated)
		{		
			//Return the plant in the level that correspond to the plant
			APlant* CurrentPlant = *LevelPlants.FindByPredicate([PlantSaved](APlant* n) {return n->GetName() == PlantSaved.Key; });
			if (!CurrentPlant)
			{
				UE_LOG(LogTemp, Warning, TEXT("ERROR:Save File Corrupted, deleting it"), );
			}
			CurrentPlant->bActivated = PlantSaved.Value;
		}
		if (LoadGameInstance->Activated.Num() > 0)
		{
			ACheckPointPlant* CheckPointPlant = Cast<ACheckPointPlant>(*LevelPlants.FindByPredicate([LoadGameInstance](APlant* n) {return n->GetName() == LoadGameInstance->CheckPointID; }));
			for (int i = 0; i < Players.Num(); i++)
			{
				if (i < CheckPointPlant->SpawnPoints.Num())
				{
					Players[i]->SetActorLocation(CheckPointPlant->SpawnPoints[i]);
				}
				else
				{
					Players[i]->SetActorLocation(CheckPointPlant->GetActorLocation() + FVector::RightVector*i);
				}
			}
		}
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("No SaveFile Found"), );
}

bool ADarklightProjectGameMode::IsSaving()
{

	return !GameStateSaver::IsThreadFinished();
}

//* Trail Algorythm BEGIN*/
void ADarklightProjectGameMode::ResetCombo()
{
	CurrentComboPoints = 0;
	ActiveComboModifier = 0;
	ComboStageIndex = 0;
}
void ADarklightProjectGameMode::SignalBombDestruction(AActor* DestroyedBomb)
{
	SpawnedBombs.Remove(Cast<ABomb>(DestroyedBomb));
	//are we using bomb duration as the combo time window?
	if (SpawnedBombs.Num() == 0 && ComboTimeWindow<0)
	{
		ResetCombo();
	}
}
void ADarklightProjectGameMode::HandleTrailCollision_Implementation(FVector ContactPoint, ADarklightProjectCharacter* Bomber)
{
	ABomb* NewBomb = GetWorld()->SpawnActor<ABomb>(Bomber->CurrentBomb, ContactPoint, FRotator::ZeroRotator);
	NewBomb->ReceiveModifier(ComboStages[ComboStageIndex]);
	NewBomb->OnDestroyed.AddDynamic(this, &ADarklightProjectGameMode::SignalBombDestruction);
	SpawnedBombs.Add(NewBomb);
	//We prevent players too close to trigger another explosion
	for (ADarklightProjectCharacter* Player : Players)
	{
		if (Bomber->GetDistanceTo(Player)<= MinimumBombDistance)
		{
			Player->bChargedUp = false;
		}
	}
}
void ADarklightProjectGameMode::IncrementPlayerScore(float Increment)
{
	PlayerScore += Increment + Increment*ActiveComboModifier;
}
void ADarklightProjectGameMode::AddComboPoint()
{
	CurrentComboPoints++;
	if (HighestCombo < CurrentComboPoints)
	{
		HighestCombo = CurrentComboPoints;
	}
	//Can we get to the next stage?
	if (ComboStageIndex+1 < ComboStages.Num() && CurrentComboPoints >= ComboStages[ComboStageIndex + 1].MinimumComboPoints)
	{
		ActiveComboModifier += ComboStages[ComboStageIndex + 1].ComboModifier;
		ComboStageIndex++;
	}
}
void ADarklightProjectGameMode::CheckTrailCollisions()
{
	/***********************************************************
						Debug
	**************************************************************/
	if (bDebugTrail)
	{
		for (int i = 0; i < SavedPoints.Num(); i++)
			for (int j = 0; j < SavedPoints[i].Num(); j++)
			{
				DrawDebugPoint(
					GetWorld(),
					SavedPoints[i][j].Location,
					4,  					//size
					FColor(i * 255, 0, 255),  //pink
					false,
					TrailQueryRate
				);
			}

	}
	if (bDebugCombo)
	{
		UE_LOG(LogTemp, Warning, TEXT("DEBUG: Combo Points:%f , Combo Level:%f"),CurrentComboPoints,ComboStageIndex);
	}
	//We clean up every expired positions
	float TimeSeconds = GetWorld()->TimeSeconds;
	for (int i = 0; i < Players.Num(); i++)
	{
		for (int j = 0; j < SavedPoints[i].Num(); j++)
		{
			if (SavedPoints[i][j].ExpirationTime < TimeSeconds)
			{
				SavedPoints[i].RemoveAt(j);
				j--;
			}
		}

	}

	for (int CurrentPlayerIndex = 0; CurrentPlayerIndex < Players.Num(); ++CurrentPlayerIndex)
	{
		FVector NewPosition = Players[CurrentPlayerIndex]->GetActorLocation();
		FTrailPoint NewPoint;
		NewPoint.Location = NewPosition;
		NewPoint.ExpirationTime = GetWorld()->TimeSeconds + Players[CurrentPlayerIndex]->TrailLenght;
		SavedPoints[CurrentPlayerIndex].Add(NewPoint);
		//If an explosion occurs, the charge will be used, else it will be given to the player so it can produce explosions again if he was discharged before
		bool bChargeUsed=false;
		//We need at least two points to make a segment. 
		if (SavedPoints[CurrentPlayerIndex].Num() > 1)
		{
			//We take the last position saved before the NewPosition we just added
			FVector LastPositionSaved = SavedPoints[CurrentPlayerIndex][SavedPoints[CurrentPlayerIndex].Num() - 2].Location;
			//We compare this new segment to every location saved by other players
			for (int PlayerComparedIndex = 0; PlayerComparedIndex < SavedPoints.Num() && !bChargeUsed; ++PlayerComparedIndex)
			{
				if (PlayerComparedIndex == CurrentPlayerIndex || SavedPoints[PlayerComparedIndex].Num()<2)//we skip the check if its lines from the same players or there isnt a line segment saved for the comparedPlayer
				{
					continue;
				}
				//We check each segments of the compared player. 3 nested loops, sorry
				for (int PointComparedIndex = 0; PointComparedIndex+1 < SavedPoints[PlayerComparedIndex].Num() && !bChargeUsed; PointComparedIndex++)
				{

					FVector NearestPointCompared, NearestPointCurrent;
					//We store the nearest points on the new segment and the compared segment and check if they are close enough for a collision
					FMath::SegmentDistToSegment(SavedPoints[PlayerComparedIndex][PointComparedIndex].Location, SavedPoints[PlayerComparedIndex][PointComparedIndex + 1].Location
						, LastPositionSaved, NewPosition, NearestPointCompared, NearestPointCurrent);
					if (FVector::Dist(NearestPointCompared, NearestPointCurrent) <= TrailDistanceTolerance)
					{
						
						//Collision Occured
						if (Players[CurrentPlayerIndex]->bChargedUp)
						{

							//We spawn a collision and disable the player future collisions until he doesnt create collisions anymore
							FVector ContactPoint = (NearestPointCompared + NearestPointCurrent) / 2;
							AddComboPoint();
							//Is it a normal time window or based on bombs 
							if (ComboTimeWindow >= 0)
							{
								//Reset the timer and starts it
								GetWorld()->GetTimerManager().ClearTimer(ComboCheckTimer);
								GetWorld()->GetTimerManager().SetTimer(ComboCheckTimer, this, &ADarklightProjectGameMode::ResetCombo, ComboTimeWindow, false);
							}
							//else the bomb will signal its destruction to us and we will see if we reset the combo then
							HandleTrailCollision(ContactPoint,Players[PlayerComparedIndex]);
						}
						bChargeUsed = true;
					}
				}
			}
		}
		Players[CurrentPlayerIndex]->bChargedUp = !bChargeUsed;
	}
}
//* Trail Algorythm END*/