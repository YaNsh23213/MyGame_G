// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "MGTCoreTypes.h"
#include "UI/MGTBaseWidget.h"
#include "MGTGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class MYGAME_API UMGTGameOverWidget : public UMGTBaseWidget
{
    GENERATED_BODY()


protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetLevelButtom;

    virtual void NativeOnInitialized() override;

private:
    void OnMatchStateChanged(EMGTMatchState State);
    void UpdatePlayerStat();

    UFUNCTION()
    void OnResetLevel();
};
