// MyGameTry, All Rights Reserved


#include "UI/MGTGameHUD.h"
#include "Engine/Canvas.h"
#include"Blueprint/UserWidget.h"
void AMGTGameHUD::BeginPlay() 
{
    Super::BeginPlay();

    auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
    if (PlayerHUDWidget)
    {
        PlayerHUDWidget->AddToViewport();
    }
}


void AMGTGameHUD::DrawHUD() 
{
    Super::DrawHUD();
    //DrawCrosshair();
}

void AMGTGameHUD::DrawCrosshair() 
{
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
    
    const float HalfLineSize = 10.0f;
    const float LineTheckness =2.0f;
    const FLinearColor LineColor = FLinearColor::Green;

    DrawLine(Center.Min - HalfLineSize,Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineTheckness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineTheckness);
}
