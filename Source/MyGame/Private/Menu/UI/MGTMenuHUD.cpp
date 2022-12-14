// MyGameTry, All Rights Reserved

#include "Menu/UI/MGTMenuHUD.h"
#include "UI/MGTBaseWidget.h"

void AMGTMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if (MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<UMGTBaseWidget>(GetWorld(), MenuWidgetClass);
        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
            MenuWidget->Show();
        }
    }
}