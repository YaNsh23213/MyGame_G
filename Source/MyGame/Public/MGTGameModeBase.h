// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MGTCoreTypes.h"
#include "MGTGameModeBase.generated.h"

const static int32 MinRoundTimeToRespawn = 10;

class AAIController;
UCLASS() class MYGAME_API AMGTGameModeBase : public AGameModeBase
{
    GENERATED_BODY()
public:
    AMGTGameModeBase();

    FOnMatchStateChangedSignature OnMatchStateChanged;

    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

    void Killed(AController* KillerController, AController* VictimController);

    FGameData GetGameData() const { return GameData; }
    int32 GetCurentRoundNum() const { return CurrentRound; }
    int32 GetRoundSecondsReaining() const { return RoundCountDown; }

    void RespawnRequest(AController* Controller);

    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
    virtual bool ClearPause() override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AICotrollerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

private:
    EMGTMatchState MatchState = EMGTMatchState::WaitToStart;
    int32 CurrentRound = 1;
    int32 RoundCountDown = 0;
    FTimerHandle GameRoundTimerHandle;

    void StartRound();
    void GameTimerUpdate();
    void SpawnBots();

    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

    void CreateTeamsInfo();
    FLinearColor DetermineColorByTeamID(int32 TeamID) const;
    void SetPlayerColor(AController* Controller);

    void LogPlayerInfo();

    void StartRespwn(AController* Controller);

    void GameOver();

    void SetMatchState(EMGTMatchState State);
};
