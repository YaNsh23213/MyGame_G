// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MGTPlayerController.generated.h"

class UMGTRespawnComponent;

UCLASS()
class MYGAME_API AMGTPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
    AMGTPlayerController();

protected:
		 UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cpmponents")
    UMGTRespawnComponent* MGTRespawnComponent;
	
};
