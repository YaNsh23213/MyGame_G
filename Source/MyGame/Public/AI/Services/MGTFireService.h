// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "MGTFireService.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMGTFireService : public UBTService
{
	GENERATED_BODY()

		public:
    UMGTFireService();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKay;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
