// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "MGTCoreTypes.h"
#include "UI/MGTBaseWidget.h"
#include "MGTMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class UMGTGameInstance;
class UMGTLevelItemWidget;
UCLASS()
class MYGAME_API UMGTMenuWidget : public UMGTBaseWidget
{
    GENERATED_BODY()
protected:
    UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* LevelItemsBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* HideAnimation;

    virtual void NativeOnInitialized() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
    UPROPERTY()
    TArray<UMGTLevelItemWidget*> LevelItemWidgets;

    UFUNCTION()
    void OnStartGame();

    UFUNCTION()
    void OnQuitGame();

    void InitLevelItems();
    void OnLevelSelected(const FLevelData& Data);
    UMGTGameInstance* GetMGTGameInstance() const;
};
