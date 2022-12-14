// MyGameTry, All Rights Reserved

#include "UI/MGTGameDataUserWidget.h"
#include "MGTGameModeBase.h"
#include "Player/MGTPlayerState.h"

int32 UMGTGameDataUserWidget::GetCurrentRoundNum() const
{
    const auto GameMode = GetMGTGameMode();
    return GameMode ? GameMode->GetCurentRoundNum() : 0;
}

int32 UMGTGameDataUserWidget::GetTotalRoundsNum() const
{
    const auto GameMode = GetMGTGameMode();
    return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 UMGTGameDataUserWidget::GetRoundSecondsRemaining() const
{
    const auto GameMode = GetMGTGameMode();
    return GameMode ? GameMode->GetRoundSecondsReaining() : 0;
}

AMGTGameModeBase* UMGTGameDataUserWidget::GetMGTGameMode() const
{
    return GetWorld() ? Cast<AMGTGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}
AMGTPlayerState* UMGTGameDataUserWidget::GetMGTPlayerState() const
{
    return GetOwningPlayer() ? Cast<AMGTPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}