// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/MGTBaseCharacter.h"
#include "MGTAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class MYGAME_API AMGTAICharacter : public AMGTBaseCharacter
{
	GENERATED_BODY()

		public:
    AMGTAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

	

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UWidgetComponent* HealthWidgetComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    float HealtVisibilityDistance = 1000.0f;

    virtual void Tick(float DeltaTime) override;


    virtual void BeginPlay() override;
    virtual void OnHealthChanged(float Health, float HealthDelta) override;

    virtual void OnDeath() override;

    private:
    void UpdateHelathWidgetVisibility();
};
