// MyGameTry, All Rights Reserved


#include "AI/EQS/EnvQueryTest_PickUpCouldBeTaken.h"
#include"EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include"Pickups/MGTBasePickup.h"

UEnvQueryTest_PickUpCouldBeTaken::UEnvQueryTest_PickUpCouldBeTaken(const FObjectInitializer& ObjectInitiliazer) 
{
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PickUpCouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const 
{
    const auto DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);
    const bool WantsBeTakable = BoolValue.GetValue();

    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        const auto ItemActor = GetItemActor(QueryInstance, It.GetIndex());
        const auto PickupActor = Cast<AMGTBasePickup>(ItemActor);
        if (!PickupActor) continue;

        const auto CouldBeTaken = PickupActor->CouldBeTaken();
        It.SetScore(TestPurpose, FilterType, CouldBeTaken, WantsBeTakable);
    }
}
