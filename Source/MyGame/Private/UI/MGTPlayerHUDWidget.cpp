// MyGameTry, All Rights Reserved

#include "UI/MGTPlayerHUDWidget.h"
#include "Components/MGTHealthComponent.h"
#include "Components/MGTWeaponComponent.h"
#include "MGTUtils.h"

bool UMGTPlayerHUDWidget::Initialize()
{
    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UMGTPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
    return Super::Initialize();
}

 void UMGTPlayerHUDWidget::OnNewPawn(APawn* NewPawn) 
 {
     const auto HealtCompopnent = MGTUtils::GetMGTPlayerComponent<UMGTHealthComponent>(NewPawn);
     if (HealtCompopnent)
     {
         HealtCompopnent->OnHealthChanged.AddUObject(this, &UMGTPlayerHUDWidget::OnHealthChanged);
     }
 }

void UMGTPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if (HealthDelta < 0.0f)
    {
        OnTakeDamage();
    }
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