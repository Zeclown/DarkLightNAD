

#pragma once
#include "Plant.h"
#include "CheckPointPlant.h"
#include "DarklightProject.h"
#include "DarklightProjectGameMode.h"
/**
 * Thread-Safe Singleton to save the state of a normal adventure game of Seasons
 */

class DARKLIGHTPROJECT_API GameStateSaver:public FRunnable
{

	/** Singleton Access*/
	static GameStateSaver* Instance;
	bool bGameSaved;
	/** Thread used for saving*/
	FRunnableThread* Thread;
	FThreadSafeCounter StopTaskCounter;
	/* Start Saving data*/
	ACheckPointPlant* CheckPoint;
	UWorld* WorldToSave;
	FString LevelName;
	int PlayerScore;
	EGameChallengeType GameMode;
	UDarklightSaveGame* SaveGameInstance;
	/* End Saving data*/


public:
	GameStateSaver(UWorld* WorldToSave, ACheckPointPlant* CheckPoint,FString LevelName,int PlayerScore, EGameChallengeType GameMode);
	~GameStateSaver();
	bool IsFinished() const
	{
		return bGameSaved;
	}

	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;

	void CheckCompletion();
	//Initialise the saver and returns a handle to it
	static GameStateSaver* SaveInit(UWorld* WorldToSave, ACheckPointPlant* CheckPoint, FString LevelName, int PlayerScore, EGameChallengeType GameMode);

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	static bool IsThreadFinished();
};
