// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/MGTBaseCharacter.h"
#include "MGTAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class MYGAME_API AMGTAICharacter : public AMGTBaseCharacter
{
	GENERATED_BODY()

		public:
    AMGTAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

protected:
    virtual void OnDeath() override;
};
