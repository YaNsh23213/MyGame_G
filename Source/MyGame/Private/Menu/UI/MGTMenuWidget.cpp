// MyGameTry, All Rights Reserved

#include "Menu/UI/MGTMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMGTMenuWidget::NativeOnInitialized() 
{
    Super::NativeOnInitialized();
    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &UMGTMenuWidget::OnStartGame);
    }
}

void UMGTMenuWidget::OnStartGame() 
{
    const FName StartLevelName = "TestLevel";

    UGameplayStatics::OpenLevel(this, StartLevelName);
}
