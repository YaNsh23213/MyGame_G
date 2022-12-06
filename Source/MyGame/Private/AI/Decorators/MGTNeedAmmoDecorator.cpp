// MyGameTry, All Rights Reserved


#include "AI/Decorators/MGTNeedAmmoDecorator.h"
#include"AIcontroller.h"
#include "MGTUtils.h"
#include"Components/MGTWeaponComponent.h"

UMGTNeedAmmoDecorator::UMGTNeedAmmoDecorator()
{
    NodeName = "Need Ammo";
}

bool UMGTNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller) return false;

    const auto WeaponComponent = MGTUtils::GetMGTPlayerComponent<UMGTWeaponComponent>(Controller->GetPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->NeedAmmo(WeaponType);
}
