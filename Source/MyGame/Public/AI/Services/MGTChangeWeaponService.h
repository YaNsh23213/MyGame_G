// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MGTChangeWeaponService.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMGTChangeWeaponService : public UBTService
{
	GENERATED_BODY()

		public:
    UMGTChangeWeaponService();

	protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Prabability = 0.5f;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
