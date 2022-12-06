// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "MGTEnemyEnvQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMGTEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
	public:
    virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

	protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName EnemyActorKeyName = "EnemyActor";
};
