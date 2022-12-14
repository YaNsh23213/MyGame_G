// MyGameTry, All Rights Reserved

#include "UI/MGTHealthBarWidget.h"
#include "components/ProgressBar.h"

void UMGTHealthBarWidget::SetHealthPercent(float Percent)
{
    if (!HealthProgeressBar) return;
    const auto HealtBarVisibility = (Percent >= PercentVisibilityThreshold || FMath::IsNearlyZero(Percent))  //
                                        ? ESlateVisibility::Hidden
                                        : ESlateVisibility::Visible;
    HealthProgeressBar->SetVisibility(HealtBarVisibility);

    const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;

    HealthProgeressBar->SetFillColorAndOpacity(HealthBarColor);

    HealthProgeressBar->SetPercent(Percent);
}