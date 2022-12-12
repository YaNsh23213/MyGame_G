// MyGameTry, All Rights Reserved


#include "Menu/MGTMenuPlayerController.h"

void AMGTMenuPlayerController::BeginPlay() 
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
}