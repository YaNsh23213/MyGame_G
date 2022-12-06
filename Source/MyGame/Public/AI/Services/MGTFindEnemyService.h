// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MGTFindEnemyService.generated.h"

/**
 *
 */
UCLASS()
class MYGAME_API UMGTFindEnemyService : public UBTService
{
    GENERATED_BODY()

public:
    UMGTFindEnemyService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKay;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
