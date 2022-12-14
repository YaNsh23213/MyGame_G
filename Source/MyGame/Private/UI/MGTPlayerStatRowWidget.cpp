// MyGameTry, All Rights Reserved

#include "UI/MGTPlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UMGTPlayerStatRowWidget::SetPlayerName(const FText& Text)
{
    if (!PlayerNameTextBlock) return;
    PlayerNameTextBlock->SetText(Text);
}
void UMGTPlayerStatRowWidget::SetKillsTextBlock(const FText& Text) 
{
    if (!KillsTextBlock) return;
    KillsTextBlock->SetText(Text);
}
void UMGTPlayerStatRowWidget::SetDeathsTextBlock(const FText& Text) 
{
    if (!DeathsTextBlock) return;
    DeathsTextBlock->SetText(Text);
}
void UMGTPlayerStatRowWidget::SetTeamTextBlock(const FText& Text) 
{
    if (!TeamTextBlock) return;
    TeamTextBlock->SetText(Text);
}
void UMGTPlayerStatRowWidget::SetPlayerIndicatorImage(bool Visible) 
{
    if (!PlayerIndicatorImage) return;
    PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UMGTPlayerStatRowWidget::SetTeamColor(const FLinearColor& Color)
{
    if (!TeamImage) return;
    TeamImage->SetColorAndOpacity(Color);
}
