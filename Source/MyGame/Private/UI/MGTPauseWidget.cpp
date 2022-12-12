// MyGameTry, All Rights Reserved

#include "UI/MGTPauseWidget.h"
#include "Gameframework/GameModeBase.h"
#include"Components/Button.h"

void UMGTPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &UMGTPauseWidget::OnClearPause);
    }
}

void UMGTPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}