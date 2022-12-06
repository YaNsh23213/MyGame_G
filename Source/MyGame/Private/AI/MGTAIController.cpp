// MyGameTry, All Rights Reserved


#include "AI/MGTAIController.h"
#include "AI/MGTAICharacter.h"
#include "Components/MGTAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AMGTAIController::AMGTAIController() 
{
    MGTAIPerceptionComponent = CreateDefaultSubobject<UMGTAIPerceptionComponent>("MGTAIPerceptionComponent");
    SetPerceptionComponent(*MGTAIPerceptionComponent);
}

void AMGTAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto MGTCharacter = Cast<AMGTAICharacter>(InPawn);
    if (MGTCharacter)
    {
        RunBehaviorTree(MGTCharacter->BehaviorTreeAsset);
    }
}

void AMGTAIController::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    const auto AimActor = GetFocuOnActor();
    SetFocus(AimActor);
}

AActor* AMGTAIController::GetFocuOnActor() const
{
    if (!GetBlackboardComponent()) return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKayName));
}
