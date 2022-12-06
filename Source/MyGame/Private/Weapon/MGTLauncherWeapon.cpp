// MyGameTry, All Rights Reserved


#include "Weapon/MGTLauncherWeapon.h"
#include"Weapon/MGTProjecttile.h"

void AMGTLauncherWeapon::StartFire()
{
    MakeShot();
}

void AMGTLauncherWeapon::MakeShot() 
{

    if (!GetWorld()||IsAmmoEmpty()) return;

    FVector TraceStart, TraceEnd;

    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

    const FTransform SpawnTtransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    AMGTProjecttile* Projectile = GetWorld() ->SpawnActorDeferred<AMGTProjecttile>(ProjectileClass, SpawnTtransform);
    if (Projectile)
    {
        Projectile->SetShorDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTtransform);
    }
    DecreeseAmmo();
    SpawnMuzzleFX();
}
