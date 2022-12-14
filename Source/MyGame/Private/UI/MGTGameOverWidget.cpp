// MyGameTry, All Rights Reserved

#include "UI/MGTGameOverWidget.h"
#include "MGTGameModeBase.h"
#include "Player/MGTPlayerState.h"
#include "UI/MGTPlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "MGTUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

void UMGTGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetWorld())
    {
        const auto GameMode = Cast<AMGTGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &UMGTGameOverWidget::OnMatchStateChanged);
        }
    }
    if (ResetLevelButtom)
    {
        ResetLevelButtom->OnClicked.AddDynamic(this, &UMGTGameOverWidget::OnResetLevel);
    }
}

void UMGTGameOverWidget::OnMatchStateChanged(EMGTMatchState State)
{
    if (State == EMGTMatchState::GameOver)
    {
        UpdatePlayerStat();
    }
}
void UMGTGameOverWidget::UpdatePlayerStat()
{

    PlayerStatBox->ClearChildren();

    if (!GetWorld() || !PlayerStatBox) return;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Cast<AMGTPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        const auto PlayerStatRowWidget = CreateWidget<UMGTPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
        if (!PlayerStatRowWidget) continue;

        PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStatRowWidget->SetKillsTextBlock(MGTUtils::TextFromInt(PlayerState->GetKillsNum()));
        PlayerStatRowWidget->SetDeathsTextBlock(MGTUtils::TextFromInt(PlayerState->GetDeathNum()));
        PlayerStatRowWidget->SetTeamTextBlock(MGTUtils::TextFromInt(PlayerState->GetTeamID()));
        PlayerStatRowWidget->SetPlayerIndicatorImage(Controller->IsPlayerController());
        PlayerStatRowWidget->SetTeamColor(PlayerState->GetTeamColor());

        PlayerStatBox->AddChild(PlayerStatRowWidget);
    }
}

void UMGTGameOverWidget::OnResetLevel() 
{
    const FString CurretLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurretLevelName));
}