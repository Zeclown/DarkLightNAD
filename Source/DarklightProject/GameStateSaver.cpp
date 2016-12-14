

#include "DarklightProject.h"
#include "GameStateSaver.h"
GameStateSaver* GameStateSaver::Instance = NULL;



GameStateSaver::GameStateSaver(UWorld* WorldToSave, ACheckPointPlant* CheckPoint, FString LevelName, int PlayerScore, EGameChallengeType GameMode)
	:WorldToSave(WorldToSave), CheckPoint(CheckPoint),LevelName(LevelName),PlayerScore(PlayerScore), StopTaskCounter(0),bGameSaved(false), GameMode(GameMode)
{
	Thread = FRunnableThread::Create(this, TEXT("GameSave"), 0, TPri_BelowNormal);
}

GameStateSaver::~GameStateSaver()
{
	delete Thread;
	Thread = nullptr;
}

bool GameStateSaver::Init()
{
	SaveGameInstance = Cast<UDarklightSaveGame>(UGameplayStatics::CreateSaveGameObject(UDarklightSaveGame::StaticClass()));
	if(CheckPoint)
		SaveGameInstance->CheckPointID = CheckPoint->GetName();
	SaveGameInstance->LevelName = LevelName;
	SaveGameInstance->PlayerScore = PlayerScore;
	SaveGameInstance->GameMode = (uint8)GameMode;
	return true;
}

uint32 GameStateSaver::Run()
{
	FPlatformProcess::Sleep(0.03);
	for (TObjectIterator<APlant> Itr; Itr && StopTaskCounter.GetValue() == 0 && !IsFinished(); ++Itr)
	{
		if (Itr->GetWorld() != WorldToSave)
		{
			continue;
		}
		SaveGameInstance->Activated.Add(Itr->GetName(), Itr->bActivated);
	}
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, 1);
	bGameSaved = true;
	return 0;
}

void GameStateSaver::Stop()
{
	StopTaskCounter.Increment();
}

void GameStateSaver::CheckCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

GameStateSaver * GameStateSaver::SaveInit(UWorld* WorldToSave, ACheckPointPlant* CheckPoint, FString LevelName, int PlayerScore, EGameChallengeType GameMode)
{
	//Create new instance of thread if it does not exist
	//		and the platform supports multi threading!
	Shutdown();
	if (!Instance && FPlatformProcess::SupportsMultithreading())
	{
		Instance = new GameStateSaver(WorldToSave, CheckPoint, LevelName, PlayerScore,GameMode);
	}
	return Instance;
}

void GameStateSaver::Shutdown()
{
	if (Instance)
	{
		Instance->CheckCompletion();
		delete Instance;
		Instance = nullptr;
	}
}

bool GameStateSaver::IsThreadFinished()
{
	if (Instance) 
		return Instance->IsFinished();
	return true;
}
