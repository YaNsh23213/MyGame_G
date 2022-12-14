// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MGTGoToMenuWidget.generated.h"

class UButton;
UCLASS()
class MYGAME_API UMGTGoToMenuWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* GoToMenuButton;

    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnGoToMenu();
};
