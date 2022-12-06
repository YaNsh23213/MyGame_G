// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/MGTBaseWeapon.h"
#include "MGTLauncherWeapon.generated.h"

class AMGTProjecttile;

UCLASS()
class MYGAME_API AMGTLauncherWeapon : public AMGTBaseWeapon
{
	GENERATED_BODY()

public:
    virtual void StartFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AMGTProjecttile> ProjectileClass;
    float TimeBetweenShots = 0.1;

    virtual void MakeShot() override;
	
};
