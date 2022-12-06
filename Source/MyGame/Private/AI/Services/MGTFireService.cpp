// MyGameTry, All Rights Reserved


#include "AI/Services/MGTFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "MGTUtils.h"
#include "Components/MGTWeaponComponent.h"

UMGTFireService::UMGTFireService() 
{
    NodeName = "Fire";
}

void UMGTFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKay.SelectedKeyName);
    if (Controller)
    {
        const auto WeaponComponent = MGTUtils::GetMGTPlayerComponent<UMGTWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent)
        {
            HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
    }
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
