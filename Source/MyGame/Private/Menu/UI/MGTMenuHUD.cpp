// MyGameTry, All Rights Reserved

#include "Menu/UI/MGTMenuHUD.h"
#include "Blueprint/UserWidget.h"

void AMGTMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if (MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
        }
    }
}