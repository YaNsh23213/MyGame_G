// MyGameTry, All Rights Reserved

#include "UI/MGTPlayerHUDWidget.h"
#include "Components/MGTHealthComponent.h"
#include "Components/MGTWeaponComponent.h"
#include "MGTUtils.h"
#include "Components/ProgressBar.h"
#include "Player/MGTPlayerState.h"

void UMGTPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UMGTPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
}

void UMGTPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
    const auto HealtCompopnent = MGTUtils::GetMGTPlayerComponent<UMGTHealthComponent>(NewPawn);
    if (HealtCompopnent)
    {
        HealtCompopnent->OnHealthChanged.AddUObject(this, &UMGTPlayerHUDWidget::OnHealthChanged);
    }

    UpdateHealthBar();
}

void UMGTPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if (HealthDelta < 0.0f)
    {
        OnTakeDamage();

        if (!IsAnimationPlaying(DamageAnimation))
        {
            PlayAnimation(DamageAnimation);
        }
    }

    UpdateHealthBar();
}

float UMGTPlayerHUDWidget::GetHealthPercent() const
{
    const auto HealtCompopnent = MGTUtils::GetMGTPlayerComponent<UMGTHealthComponent>(GetOwningPlayerPawn());
    if (!HealtCompopnent) return 0.0f;

    return HealtCompopnent->GetHealthPercent();
}

bool UMGTPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponCompopnent = MGTUtils::GetMGTPlayerComponent<UMGTWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponCompopnent) return false;

    return WeaponCompopnent->GetCurrentWeaponUIData(UIData);
}

bool UMGTPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto WeaponCompopnent = MGTUtils::GetMGTPlayerComponent<UMGTWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponCompopnent) return false;

    return WeaponCompopnent->GetCurrentWeaponAmmoData(AmmoData);
}
bool UMGTPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealtCompopnent = MGTUtils::GetMGTPlayerComponent<UMGTHealthComponent>(GetOwningPlayerPawn());
    return HealtCompopnent && !HealtCompopnent->IsDead();
}
bool UMGTPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

int32 UMGTPlayerHUDWidget::GetKillsNun() const
{
    const auto Controller = GetOwningPlayer();
    if (!Controller) return 0;
    const auto PlayerState = Cast<AMGTPlayerState>(Controller->PlayerState);
    return PlayerState ? PlayerState->GetKillsNum() : 0;
}

void UMGTPlayerHUDWidget::UpdateHealthBar()
{
    if (HealthProgressBar)
    {
        HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
    }
}

FString UMGTPlayerHUDWidget::ForamatBullets(int32 BulletsNum) const
{
    const int32 MaxLen = 3;
    const TCHAR PrefixSymnol = '0';

    auto BullerStr = FString ::FromInt(BulletsNum);
    const auto SynbolsNumToAdd = MaxLen - BullerStr.Len();

    if (SynbolsNumToAdd > 0)
    {
        BullerStr = FString::ChrN(SynbolsNumToAdd, PrefixSymnol).Append(BullerStr);
    }
    return BullerStr;
}