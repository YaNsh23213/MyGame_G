// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MGTGameDataUserWidget.generated.h"

class AMGTGameModeBase;
class AMGTPlayerState;
UCLASS()
class MYGAME_API UMGTGameDataUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentRoundNum() const;
    UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetTotalRoundsNum() const;
    UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetRoundSecondsRemaining() const;

	private:

		AMGTGameModeBase* GetMGTGameMode() const;
        AMGTPlayerState* GetMGTPlayerState() const;
};
