// MyGameTry, All Rights Reserved

#include "UI/MGTGameHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "MGTGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogMGTGameHUD, All, All);

void AMGTGameHUD::BeginPlay()
{
    Super::BeginPlay();

    GameWidgets.Add(EMGTMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(EMGTMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(EMGTMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

    for (auto GameWidetPair : GameWidgets)
    {
        const auto GameWidet = GameWidetPair.Value;
        if (!GameWidet) continue;

        GameWidet->AddToViewport();
        GameWidet->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto GameMode = Cast<AMGTGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &AMGTGameHUD::OnMatchStateChanged);
        }
    }
}

void AMGTGameHUD::DrawHUD()
{
    Super::DrawHUD();
    // DrawCrosshair();
}

void AMGTGameHUD::DrawCrosshair()
{
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    const float HalfLineSize = 10.0f;
    const float LineTheckness = 2.0f;
    const FLinearColor LineColor = FLinearColor::Green;

    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineTheckness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineTheckness);
}

void AMGTGameHUD::OnMatchStateChanged(EMGTMatchState State)
{
    if (CurentWidget)
    {
        CurentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets.Contains(State))
    {
        CurentWidget = GameWidgets[State];
    }

    if (CurentWidget)
    {
        CurentWidget->SetVisibility(ESlateVisibility::Visible);
    }
    UE_LOG(LogMGTGameHUD, Display, TEXT("Mathc state changed: %s"), *UEnum::GetValueAsString(State));
}
