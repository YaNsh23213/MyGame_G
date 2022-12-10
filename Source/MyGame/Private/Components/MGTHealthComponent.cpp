// MyGameTry, All Rights Reserved

#include "Components/MGTHealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include "MGTGamemodeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

UMGTHealthComponent::UMGTHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}
bool UMGTHealthComponent::TryToAddHealth(float HealthAmount)
{
    if (IsDead() || IsHealthFull()) return false;
    SetHealth(Health + HealthAmount);
    return true;
}
bool UMGTHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}
void UMGTHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxHealth > 0);

    SetHealth(MaxHealth);

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UMGTHealthComponent::OnTakeAnyDamage);
    }
}

void UMGTHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
    SetHealth(Health - Damage);

    GetWorld()->GetTimerManager().ClearTimer(HealTimeHandle);

    if (IsDead())
    {
        Killed(InstigatedBy);
        OnDeath.Broadcast();
    }
    else if (AutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimeHandle, this, &UMGTHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
    }
    PlayCameraShake();
}

void UMGTHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);

    if (IsHealthFull() && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimeHandle);
    }
}

void UMGTHealthComponent::SetHealth(float NewHealth)
{
    const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const auto HealthDelta = NextHealth - Health;

    Health = NextHealth;
    OnHealthChanged.Broadcast(Health, HealthDelta);
}

void UMGTHealthComponent::PlayCameraShake()
{
    if (IsDead()) return;

    const auto Player = Cast<APawn>(GetOwner());
    if (!Player) return;

    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller || !Controller->PlayerCameraManager) return;

    Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

void UMGTHealthComponent::Killed(AController* KillerController)
{
    if (!GetWorld()) return;
    const auto GameMode = Cast<AMGTGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode) return;

    const auto Player = Cast<APawn>(GetOwner());
    const auto VictimController = Player ? Player->Controller : nullptr;

    GameMode->Killed(KillerController,VictimController);

}
