// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "DarklightProject.h"
#include "DarklightProjectGameMode.h"
#include "DrawDebugHelpers.h"
#include "Engine.h"
#include "Engine/Blueprint.h"

ADarklightProjectGameMode::ADarklightProjectGameMode()
{
	TrailQueryRate = 0.05f;
	SegmentsToSkip = 0;
	TrailDistanceTolerance = 15;

}
void ADarklightProjectGameMode::BeginPlay()
{
	Super::BeginPlay();
	//Set Timer for  trail collision check
	GetWorld()->GetTimerManager().SetTimer(TrailCheckTimer, this, &ADarklightProjectGameMode::CheckTrailCollisions, TrailQueryRate, true);
	//Find players in game
	for (TObjectIterator<ADarklightProjectCharacter> Itr; Itr; ++Itr)
	{
		if (Itr->GetWorld() != GetWorld())
		{
			continue;
		}
		Players.Add(*Itr);
		PlayersTrailTimers.Add((*Itr)->TrailLenght);
		SavedPoints.Add(TArray<FVector>());
	}
}
void ADarklightProjectGameMode::CheckTrailCollisions()
{
	/***********************************************************
						Debug
	**************************************************************/
	for(int i =0;i<SavedPoints.Num();i++)
		for (int j = 0; j < SavedPoints[i].Num(); j++)
		{
			DrawDebugPoint(
				GetWorld(),
				SavedPoints[i][j],
				4,  					//size
				FColor(i*255, 0, 255),  //pink
				false,  				
				TrailQueryRate				
			);
		}



	//We clean up every expired positions
	for (int i = 0; i < Players.Num(); i++)
	{
		if (PlayersTrailTimers[i] > 0)
		{
			PlayersTrailTimers[i] -= TrailQueryRate;
		}
		else
		{
			//We add the seconds that were stored in the player timer to the query rate
			SavedPoints[i].RemoveAt(0, 1);
		}

	}

	for (int CurrentPlayerIndex = 0; CurrentPlayerIndex < Players.Num(); ++CurrentPlayerIndex)
	{
		FVector NewPosition = Players[CurrentPlayerIndex]->GetActorLocation();
		SavedPoints[CurrentPlayerIndex].Add(NewPosition);
		//If an explosion occurs, the charge will be used, else it will be given to the player so it can produce explosions again if he was discharged before
		bool bChargeUsed=false;
		//We need at least two points to make a segment. 
		if (SavedPoints[CurrentPlayerIndex].Num() > 1)
		{
			//We take the last position saved before the NewPosition we just added
			FVector LastPositionSaved = SavedPoints[CurrentPlayerIndex][SavedPoints[CurrentPlayerIndex].Num() - 2];
			//We compare this new segment to every location saved by other players
			for (int PlayerComparedIndex = 0; PlayerComparedIndex < SavedPoints.Num(); ++PlayerComparedIndex)
			{
				if (PlayerComparedIndex == CurrentPlayerIndex || SavedPoints[PlayerComparedIndex].Num()<2)//we skip the check if its lines from the same players or there isnt a line segment saved for the comparedPlayer
				{
					continue;
				}
				//We check each segments of the compared player. 3 nested loops, sorry
				for (int PointComparedIndex = 0; PointComparedIndex+1 < SavedPoints[PlayerComparedIndex].Num(); PointComparedIndex+=2)
				{
					FVector NearestPointCompared, NearestPointCurrent;
					//We store the nearest points on the new segment and the compared segment and check if they are close enough for a collision
					FMath::SegmentDistToSegment(SavedPoints[PlayerComparedIndex][PointComparedIndex], SavedPoints[PlayerComparedIndex][PointComparedIndex + 1]
						, LastPositionSaved, NewPosition, NearestPointCompared, NearestPointCurrent);
					if (FVector::Dist(NearestPointCompared, NearestPointCurrent) <= TrailDistanceTolerance)
					{
						
						//Collision Occured
						if (Players[CurrentPlayerIndex]->bChargedUp)
						{
							//We spawn a collision and disable the player future collisions until he doesnt create collisions anymore
							FVector ContactPoint = (NearestPointCompared + NearestPointCurrent) / 2;
							
							HandleTrailCollision(ContactPoint);
							//DrawDebugSphere(GetWorld(), ContactPoint, 40, 5, FColor(255, 0, 0), false, 3);
							////UE_LOG(LogTemp, Warning, TEXT("Collision!!Vector : (%f,%f,%f),(%f,%f,%f) nearest(%f,%f,%f)"), SavedPoints[PlayerComparedIndex][PointComparedIndex].X, SavedPoints[PlayerComparedIndex][PointComparedIndex].Y, SavedPoints[PlayerComparedIndex][PointComparedIndex].Z, SavedPoints[PlayerComparedIndex][PointComparedIndex + 1].X, SavedPoints[PlayerComparedIndex][PointComparedIndex + 1].Y, SavedPoints[PlayerComparedIndex][PointComparedIndex + 1].Z, NearestPointCompared.X, NearestPointCompared.Y, NearestPointCompared.Z);
							////UE_LOG(LogTemp, Warning, TEXT("Vector : (%f,%f,%f),(%f,%f,%f) nearest(%f,%f,%f)"), LastPositionSaved.X, LastPositionSaved.Y, LastPositionSaved.Z, NewPosition.X, NewPosition.Y, NewPosition.Z, NearestPointCurrent.X, NearestPointCurrent.Y, NearestPointCurrent.Z);
							////UE_LOG(LogTemp, Warning, TEXT("Distance Between Points %f"), FVector::Dist(NearestPointCompared, NearestPointCurrent));
						}
						bChargeUsed = true;
						break;
					}
				}
			}
		}
		Players[CurrentPlayerIndex]->bChargedUp = !bChargeUsed;
	}
}