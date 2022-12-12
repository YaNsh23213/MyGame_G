// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MGTCoreTypes.h"
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

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TMap<EMGTMatchState, UUserWidget*> GameWidgets;

    UPROPERTY()
    UUserWidget* CurentWidget = nullptr;
    void DrawCrosshair();

    void OnMatchStateChanged(EMGTMatchState State);
};
