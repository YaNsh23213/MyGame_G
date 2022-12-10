// MyGameTry, All Rights Reserved

#include "MGTGameModeBase.h"
#include "Player/MGTBaseCharacter.h"
#include "Player/MGTPlayerController.h"
#include "UI/MGTGameHUD.h"
#include "AIController.h"
#include "Player/MGTPlayerState.h"
#include "MGTUtils.h"
#include "Components/MGTRespawnComponent.h"
#include "EngineUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogMGTGameModeBase, All, All);

AMGTGameModeBase::AMGTGameModeBase()
{
    DefaultPawnClass = AMGTBaseCharacter ::StaticClass();  // Pereopredelaem default class controllera 10 i 11
    PlayerControllerClass = AMGTPlayerController::StaticClass();
    HUDClass = AMGTGameHUD::StaticClass();
    PlayerStateClass = AMGTPlayerState::StaticClass();
}

void AMGTGameModeBase::StartPlay()
{
    Super::StartPlay();
    SpawnBots();
    CreateTeamsInfo();

    CurrentRound = 1;
    StartRound();
}

UClass* AMGTGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AMGTGameModeBase::SpawnBots()
{
    if (!GetWorld()) return;
    for (int32 i = 0; i < GameData.PlayersNum - 1; i++)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        const auto MGTAIController = GetWorld()->SpawnActor<AAIController>(AICotrollerClass, SpawnInfo);
        RestartPlayer(MGTAIController);
    }
}

void AMGTGameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AMGTGameModeBase::GameTimerUpdate, 1.0f, true);
}
void AMGTGameModeBase::GameTimerUpdate()
{
    UE_LOG(LogMGTGameModeBase, Display, TEXT("Time: %i / Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsNum);

    if (--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

        if (CurrentRound + 1 <= GameData.RoundsNum)
        {
            ++CurrentRound;
            StartRound();
            ResetPlayers();
        }
        else
        {
            GameOver();
        }
    }
}

void AMGTGameModeBase::ResetPlayers()
{
    if (!GetWorld()) return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}
void AMGTGameModeBase::ResetOnePlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void AMGTGameModeBase::CreateTeamsInfo()
{
    if (!GetWorld()) return;

    int32 TeamID = 1;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;
        const auto PlayerState = Cast<AMGTPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        PlayerState->SetTeamID(TeamID);
        PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
        SetPlayerColor(Controller);
        TeamID = TeamID == 1 ? 2 : 1;
    }
}
FLinearColor AMGTGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
    if (TeamID - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamID - 1];
    }
    UE_LOG(
        LogMGTGameModeBase, Warning, TEXT("No color for team id: %i, set to default: %s"), TeamID, *GameData.DefaultTeamColor.ToString());
    return GameData.DefaultTeamColor;
}
void AMGTGameModeBase::SetPlayerColor(AController* Controller)
{
    if (!Controller) return;

    const auto Character = Cast<AMGTBaseCharacter>(Controller->GetPawn());
    if (!Character) return;

    const auto PlayerState = Cast<AMGTPlayerState>(Controller->PlayerState);
    if (!PlayerState) return;

    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void AMGTGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
    const auto KillerPlayerState = KillerController ? Cast<AMGTPlayerState>(KillerController->PlayerState) : nullptr;
    const auto VictimPlayerState = VictimController ? Cast<AMGTPlayerState>(VictimController->PlayerState) : nullptr;

    if (KillerPlayerState)
    {
        KillerPlayerState->AddKill();
    }
    if (VictimPlayerState)
    {
        VictimPlayerState->AddDeath();
    }

    StartRespwn(VictimController);
}

void AMGTGameModeBase::LogPlayerInfo()
{
    if (!GetWorld()) return;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Cast<AMGTPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        PlayerState->LogInfo();
    }
}

void AMGTGameModeBase::StartRespwn(AController* Controller)
{

    const auto RespawnAviable = RoundCountDown > MinRoundTimeToRespawn + GameData.RespawnTime;
    if (!RespawnAviable) return;
    const auto RespawnComponent = MGTUtils::GetMGTPlayerComponent<UMGTRespawnComponent>(Controller);
    if (!RespawnComponent) return;

    RespawnComponent->Respawn(GameData.RespawnTime);
}

void AMGTGameModeBase::RespawnRequest(AController* Controller)
{
    ResetOnePlayer(Controller);
}

void AMGTGameModeBase::GameOver()
{
    UE_LOG(LogMGTGameModeBase, Display, TEXT("===========Game Over==========="));
    LogPlayerInfo();

    for (auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }
}