// MyGameTry, All Rights Reserved

#include "Player/MGTPlayerController.h"
#include "Components/MGTRespawnComponent.h"
#include "MGTGameModeBase.h"

AMGTPlayerController::AMGTPlayerController()
{
    MGTRespawnComponent = CreateDefaultSubobject<UMGTRespawnComponent>("MGTRespawnComponent");
}

void AMGTPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GetWorld())
    {
        const auto GameMode = Cast<AMGTGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &AMGTPlayerController::OnMatchStateChanged);
        }
    }
}
void AMGTPlayerController::OnMatchStateChanged(EMGTMatchState State)
{
    if (State == EMGTMatchState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

void AMGTPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!InputComponent) return;

    InputComponent->BindAction("PauseGame", IE_Pressed, this, &AMGTPlayerController::OnPauseGame);
}

void AMGTPlayerController::OnPauseGame()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->SetPause(this);
}