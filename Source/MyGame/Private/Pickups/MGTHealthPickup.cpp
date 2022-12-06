// MyGameTry, All Rights Reserved


#include "Pickups/MGTHealthPickup.h"
#include "Components/MGTHealthComponent.h"
#include "MGTUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All)

bool AMGTHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = MGTUtils::GetMGTPlayerComponent<UMGTHealthComponent>(PlayerPawn);
    if (!HealthComponent) return false;

    return HealthComponent->TryToAddHealth(HealthAmount);
}
