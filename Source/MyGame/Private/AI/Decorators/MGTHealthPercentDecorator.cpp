// MyGameTry, All Rights Reserved


#include "AI/Decorators/MGTHealthPercentDecorator.h"
#include"AIcontroller.h"
#include "MGTUtils.h"
#include"Components/MGTHealthComponent.h"

UMGTHealthPercentDecorator::UMGTHealthPercentDecorator() 
{
    NodeName = "HealthPercent";
}

bool UMGTHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller) return false;

    const auto HealthComponent = MGTUtils::GetMGTPlayerComponent<UMGTHealthComponent>(Controller->GetPawn());
    if (!HealthComponent || HealthComponent->IsDead()) return false;

    return HealthComponent->GetHealthPercent() <= HealthPercent;
}
