// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "MGTHealthPercentDecorator.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMGTHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()
		public:
    UMGTHealthPercentDecorator();
	protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float HealthPercent = 0.6f;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
