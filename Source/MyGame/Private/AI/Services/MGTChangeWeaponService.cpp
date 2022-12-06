// MyGameTry, All Rights Reserved

#include "AI/Services/MGTChangeWeaponService.h"
#include "Components/MGTWeaponComponent.h"
#include "AIController.h"
#include "MGTUtils.h"

UMGTChangeWeaponService::UMGTChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void UMGTChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (Controller)
    {
        const auto WeaponComponent = MGTUtils::GetMGTPlayerComponent<UMGTWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent && Prabability > 0 && FMath::FRand() <= Prabability)
        {
            WeaponComponent->NextWeapon();
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
