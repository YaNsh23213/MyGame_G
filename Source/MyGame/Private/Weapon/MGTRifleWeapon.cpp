// MyGameTry, All Rights Reserved

#include "Weapon/MGTRifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Weapon/Components/MGTWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"



AMGTRifleWeapon::AMGTRifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<UMGTWeaponFXComponent>("WeaponComponent");
}

void AMGTRifleWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponFXComponent);
}

void AMGTRifleWeapon::StartFire()
{
    InitMuzzleFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AMGTRifleWeapon::MakeShot, TimeBetweenShots, true);
    MakeShot();
}
void AMGTRifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetMuzzleFXVisibility(false);
}

void AMGTRifleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
    {
        StopFire();
        return;
    };

    FVector TraceStart, TraceEnd;

    if (!GetTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    };

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    FVector TraceFXEnd = TraceEnd;
    if (HitResult.bBlockingHit)
    {
        TraceFXEnd = HitResult.ImpactPoint;
        MakeDamage(HitResult);
        WeaponFXComponent->PlayImapctFX(HitResult);
    }
    SpawnTraceFX(GetMuzzleWorldLocation(),TraceFXEnd);
    DecreeseAmmo();
}
bool AMGTRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const auto HalfRad = FMath::DegreesToRadians(BulletSpead);
    const FVector ShoorDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    TraceEnd = TraceStart + ShoorDirection * TraceMaxDistance;
    return true;
}
void AMGTRifleWeapon::MakeDamage(const FHitResult& HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor) return;

    DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}

void AMGTRifleWeapon::InitMuzzleFX()
{
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent=SpawnMuzzleFX();
    }
    SetMuzzleFXVisibility(true);
}
void AMGTRifleWeapon::SetMuzzleFXVisibility(bool Visible)
{
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent ->SetPaused(!Visible);
        MuzzleFXComponent->SetVisibility(Visible, true);
    }
}

void AMGTRifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd) 
{
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}