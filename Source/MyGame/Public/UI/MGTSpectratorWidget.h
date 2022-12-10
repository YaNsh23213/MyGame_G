// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MGTSpectratorWidget.generated.h"

/**
 *
 */
UCLASS()
class MYGAME_API UMGTSpectratorWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetRespawnTime(int32& CiuntDownTime) const;
};
