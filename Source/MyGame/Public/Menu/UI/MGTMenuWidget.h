// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MGTMenuWidget.generated.h"

class UButton;
UCLASS()
class MYGAME_API UMGTMenuWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
    
    UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;

    virtual void NativeOnInitialized() override;

    private:
    UFUNCTION()
    void OnStartGame();
};
