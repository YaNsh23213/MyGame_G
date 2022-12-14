// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MGTBaseWidget.generated.h"

UCLASS()
class MYGAME_API UMGTBaseWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    void Show();

protected:
    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation* ShowAnimation;
};
