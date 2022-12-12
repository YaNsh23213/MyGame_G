// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MGTPauseWidget.generated.h"
class UButton;
UCLASS()
class MYGAME_API UMGTPauseWidget : public UUserWidget
{
    GENERATED_BODY()



protected:
    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnClearPause();
};
