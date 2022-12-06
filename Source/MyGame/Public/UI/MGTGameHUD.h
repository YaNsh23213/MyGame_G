// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MGTGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AMGTGameHUD : public AHUD
{
	GENERATED_BODY()

		public:
    virtual void DrawHUD() override;

	protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	virtual void BeginPlay() override;

		private:
    void DrawCrosshair();
	
};
