// MyGameTry, All Rights Reserved


#include "AI/Tasks/MTGNextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"


UMTGNextLocationTask::UMTGNextLocationTask()
{
    NodeName = "NextLocztion";
}

EBTNodeResult::Type UMTGNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blaclboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blaclboard) return EBTNodeResult::Failed;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return EBTNodeResult::Failed;

    const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
    if (!NavSys) return EBTNodeResult::Failed;

    FNavLocation NavLocation;
    auto Location = Pawn->GetActorLocation();
    if (!SelfCenter)
    {
        auto CenterActor = Cast<AActor>(Blaclboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
        if (!CenterActor) return EBTNodeResult::Failed;
        Location = CenterActor->GetActorLocation();
    }

    const auto Found = NavSys->GetRandomReachablePointInRadius(Location, Radius, NavLocation);
    if (!Found) return EBTNodeResult::Failed;

    Blaclboard->SetValueAsVector(AimLocationKey.SelectedKeyName,NavLocation.Location);
    return EBTNodeResult::Succeeded;

    return EBTNodeResult::Type();
}
