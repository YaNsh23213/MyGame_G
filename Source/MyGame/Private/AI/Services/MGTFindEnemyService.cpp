// MyGameTry, All Rights Reserved


#include "AI/Services/MGTFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include"MGTUtils.h"
#include "Components/MGTAIPerceptionComponent.h"

UMGTFindEnemyService::UMGTFindEnemyService() 
{
    NodeName = "Find Enemy";
}

void UMGTFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    const auto BlackBoard = OwnerComp.GetBlackboardComponent();
    if (BlackBoard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = MGTUtils::GetMGTPlayerComponent<UMGTAIPerceptionComponent>(Controller);
        if (PerceptionComponent)
        {
            BlackBoard->SetValueAsObject(EnemyActorKay.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
