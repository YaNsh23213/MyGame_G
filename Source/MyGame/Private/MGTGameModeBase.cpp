// MyGameTry, All Rights Reserved


#include "MGTGameModeBase.h"
#include "Player/MGTBaseCharacter.h"
#include "Player/MGTPlayerController.h"
#include "UI/MGTGameHUD.h"

AMGTGameModeBase::AMGTGameModeBase()
{
    DefaultPawnClass = AMGTBaseCharacter ::StaticClass(); //Pereopredelaem default class controllera 10 i 11 
    PlayerControllerClass = AMGTPlayerController::StaticClass();
    HUDClass = AMGTGameHUD::StaticClass();
}

