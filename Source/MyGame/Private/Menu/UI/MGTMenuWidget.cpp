// MyGameTry, All Rights Reserved

#include "Menu/UI/MGTMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MGTGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "Menu/UI/MGTLevelItemWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogMGTMenuWidget, All, All);

void UMGTMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &UMGTMenuWidget::OnStartGame);
    }
    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &UMGTMenuWidget::OnQuitGame);
    }

    InitLevelItems();
}

void UMGTMenuWidget::InitLevelItems()
{
    const auto MGTGameIntsnce = GetMGTGameInstance();
    if (!MGTGameIntsnce) return;
    checkf(MGTGameIntsnce->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

    if (!LevelItemsBox) return;
    LevelItemsBox->ClearChildren();

    for (auto LevelData : MGTGameIntsnce->GetLevelsData())
    {
        const auto LevelItemWidget = CreateWidget<UMGTLevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (!LevelItemWidget) continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &UMGTMenuWidget::OnLevelSelected);

        LevelItemsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }
    if (MGTGameIntsnce->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(MGTGameIntsnce->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(MGTGameIntsnce->GetStartupLevel());
    }

}


void UMGTMenuWidget::OnLevelSelected(const FLevelData& Data) 
{
    const auto MGTGameIntsnce = GetMGTGameInstance();
    if (!MGTGameIntsnce) return;

    MGTGameIntsnce->SetStartupLevel(Data);
    for (auto LevelItemWidget : LevelItemWidgets)
    {
        if (LevelItemWidget)
        {
            const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}


void UMGTMenuWidget::OnStartGame()
{
    PlayAnimation(HideAnimation);
}
void UMGTMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) 
{
    if (Animation != HideAnimation) return;
    const auto MGTGameIntsnce = GetMGTGameInstance();
    if (!MGTGameIntsnce) return;

    UGameplayStatics::OpenLevel(this, MGTGameIntsnce->GetStartupLevel().LevelName);
}


void UMGTMenuWidget::OnQuitGame() 
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

UMGTGameInstance* UMGTMenuWidget::GetMGTGameInstance() const
{
    if (!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<UMGTGameInstance>();
}