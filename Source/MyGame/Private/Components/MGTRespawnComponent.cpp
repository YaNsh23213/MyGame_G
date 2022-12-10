// MyGameTry, All Rights Reserved

#include "Components/MGTRespawnComponent.h"
#include "MGTGameModeBase.h"

UMGTRespawnComponent::UMGTRespawnComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UMGTRespawnComponent::Respawn(int32 RespawnTime)
{
    if (!GetWorld()) return;
    RespawnCountDown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UMGTRespawnComponent::RespawnTimerUpadate, 1.0f, true);
}

void UMGTRespawnComponent::RespawnTimerUpadate() 
{
    if (--RespawnCountDown == 0)
    {
        if (!GetWorld()) return;
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

        const auto GameMode = Cast<AMGTGameModeBase>(GetWorld()->GetAuthGameMode());
        if (!GameMode) return;

        GameMode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}

bool UMGTRespawnComponent::IsRespawnInProgress() const 
{
    return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}
