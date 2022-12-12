// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MGTMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AMGTMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
   virtual void BeginPlay() override;
};
