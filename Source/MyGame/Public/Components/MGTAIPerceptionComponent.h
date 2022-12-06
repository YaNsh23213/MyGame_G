// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "MGTAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMGTAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

		public:
    AActor* GetClosestEnemy() const;
	
};
