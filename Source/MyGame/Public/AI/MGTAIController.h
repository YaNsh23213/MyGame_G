// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MGTAIController.generated.h"

class UMGTAIPerceptionComponent;

UCLASS()
class MYGAME_API AMGTAIController : public AAIController
{
    GENERATED_BODY()
public:
    AMGTAIController();



protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Cpmponents")
    UMGTAIPerceptionComponent* MGTAIPerceptionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKayName = "EnemyActor";

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaTime) override;

private:
    AActor* GetFocuOnActor() const;

};
