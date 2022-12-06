// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "MGTNeedAmmoDecorator.generated.h"

class AMGTBaseWeapon;
UCLASS()
class MYGAME_API UMGTNeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
    UMGTNeedAmmoDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<AMGTBaseWeapon> WeaponType;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
