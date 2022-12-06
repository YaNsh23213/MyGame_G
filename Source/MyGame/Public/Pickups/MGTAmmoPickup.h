// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Pickups/MGTBasePickup.h"
#include "MGTAmmoPickup.generated.h"

class AMGTBaseWeapon;
UCLASS()
class MYGAME_API AMGTAmmoPickup : public AMGTBasePickup
{
	GENERATED_BODY()
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
    int32 ClipsAmount = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
    TSubclassOf<AMGTBaseWeapon> WeaponType;


private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
