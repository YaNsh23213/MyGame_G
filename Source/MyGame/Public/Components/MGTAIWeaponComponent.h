// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/MGTWeaponComponent.h"
#include "MGTAIWeaponComponent.generated.h"

/**
 *
 */
UCLASS()
class MYGAME_API UMGTAIWeaponComponent : public UMGTWeaponComponent
{
    GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void NextWeapon() override;
};
