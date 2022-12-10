// MyGameTry, All Rights Reserved


#include "UI/MGTSpectratorWidget.h"
#include"MGTUtils.h"
#include"Components/MGTRespawnComponent.h"

bool UMGTSpectratorWidget::GetRespawnTime(int32& CiuntDownTime) const
{
    const auto RespawnComponent = MGTUtils::GetMGTPlayerComponent<UMGTRespawnComponent>(GetOwningPlayer());
    if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

    CiuntDownTime = RespawnComponent->GetRespawnCountDown();
    return true;

}