// MyGameTry, All Rights Reserved

#include "UI/MGTGoToMenuWidget.h"
#include "MGTGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogMGTGoToMenuWidget, All, All);

void UMGTGoToMenuWidget::NativeOnInitialized() 
{
    Super::NativeOnInitialized();

    if (GoToMenuButton)
    {
        GoToMenuButton->OnClicked.AddDynamic(this, &UMGTGoToMenuWidget::OnGoToMenu);
    }
}

void UMGTGoToMenuWidget::OnGoToMenu()
{
    if (!GetWorld()) return;

    const auto MGTGameInstance = GetWorld()->GetGameInstance<UMGTGameInstance>();
    if (!MGTGameInstance) return;

    if (MGTGameInstance->GetMenuLevelName().IsNone())
    {

        UE_LOG(LogMGTGoToMenuWidget, Error, TEXT("Menu level name is none"));
        return;
    }
    UGameplayStatics::OpenLevel(this, MGTGameInstance->GetMenuLevelName());
}
