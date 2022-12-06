// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickUpCouldBeTaken.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UEnvQueryTest_PickUpCouldBeTaken : public UEnvQueryTest
{
    GENERATED_BODY()
public:
    UEnvQueryTest_PickUpCouldBeTaken(const FObjectInitializer& ObjectInitiliazer);

    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
