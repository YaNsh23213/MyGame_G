// MyGameTry, All Rights Reserved


#include "Menu/MGTMenuGameModeBase.h"
#include"Menu/MGTMenuPlayerController.h"
#include"Menu/UI/MGTMenuHUD.h"

AMGTMenuGameModeBase::AMGTMenuGameModeBase() 
{
    PlayerControllerClass = AMGTMenuPlayerController::StaticClass();
    HUDClass = AMGTMenuHUD::StaticClass();
}