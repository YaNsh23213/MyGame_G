// MyGameTry, All Rights Reserved


#include "Pickups/MGTAmmoPickup.h"
#include "Components/MGTHealthComponent.h"
#include "Components/MGTWeaponComponent.h"
#include "MGTUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool AMGTAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = MGTUtils::GetMGTPlayerComponent<UMGTHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead()) return false;
   
     const auto WeaponComponent = MGTUtils::GetMGTPlayerComponent<UMGTWeaponComponent>(PlayerPawn);
    if (!WeaponComponent) return false;
     return WeaponComponent->TryToAddAmmo(WeaponType,ClipsAmount);
}
