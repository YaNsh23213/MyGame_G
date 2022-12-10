// MyGameTry, All Rights Reserved


#include "Player/MGTPlayerController.h"
#include "Components/MGTRespawnComponent.h"

 AMGTPlayerController::AMGTPlayerController() 
 {
     MGTRespawnComponent = CreateDefaultSubobject<UMGTRespawnComponent>("MGTRespawnComponent");
 }