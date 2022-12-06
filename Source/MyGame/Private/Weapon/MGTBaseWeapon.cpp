// MyGameTry, All Rights Reserved

#include "Weapon/MGTBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
DEFINE_LOG_CATEGORY_STATIC(BaseWeaponLog, All, All);

// Sets default values
AMGTBaseWeapon::AMGTBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

bool AMGTBaseWeapon::TryToGetAmmo(int32 ClipsAmount)
{
    if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0) return false;
    if (IsAmmoEmpty())
    {
        UE_LOG(BaseWeaponLog, Warning, TEXT("Ammo is empty"));
        CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
        OnclipEmpty.Broadcast(this);
    }
    else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
    {
        const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
        if (DefaultAmmo.Clips - NextClipsAmount >= 0)
        {
            CurrentAmmo.Clips = NextClipsAmount;
            UE_LOG(BaseWeaponLog, Warning, TEXT("Clips were added"));
        }
        else
        {
            CurrentAmmo.Clips = DefaultAmmo.Clips;
            CurrentAmmo.Bullets = DefaultAmmo.Bullets;
            UE_LOG(BaseWeaponLog, Warning, TEXT("Bullets were added"));
        }
    }
    else
    {
        CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    }
    return true;
}

void AMGTBaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponMesh);
    checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count coudn't be less or equal zero"));
    checkf(DefaultAmmo.Clips > 0, TEXT("Clips count coudn't be less or equal zero"))

        CurrentAmmo = DefaultAmmo;
}

void AMGTBaseWeapon::StartFire() {}
void AMGTBaseWeapon::StopFire() {}

void AMGTBaseWeapon::MakeShot() {}

APlayerController* AMGTBaseWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return nullptr;

    return Player->GetController<APlayerController>();
}

bool AMGTBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto MGTCharacter = Cast<ACharacter>(GetOwner());
    if (!MGTCharacter) return false;

    if (MGTCharacter->IsPlayerControlled())
    {
        const auto Controller = GetPlayerController();
        if (!GetPlayerController()) return false;
        Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    }
    else
    {
        ViewLocation = GetMuzzleWorldLocation();
        ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
    }
    return true;
}

FVector AMGTBaseWeapon::GetMuzzleWorldLocation() const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool AMGTBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;
    const FVector ShoorDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShoorDirection * TraceMaxDistance;
    return true;
}

void AMGTBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
    if (!GetWorld()) return;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());
    CollisionParams.bReturnPhysicalMaterial = true;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}
void AMGTBaseWeapon::DecreeseAmmo()
{
    if (CurrentAmmo.Bullets == 0)
    {
        UE_LOG(BaseWeaponLog, Warning, TEXT("Clip is empty"));
        return;
    }

    CurrentAmmo.Bullets--;

    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        StopFire();
        OnclipEmpty.Broadcast(this);
    }
}
bool AMGTBaseWeapon::IsAmmoEmpty() const
{
    return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}
bool AMGTBaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}
void AMGTBaseWeapon::ChacgeClip()
{
    if (!CurrentAmmo.Infinite)
    {
        if (CurrentAmmo.Clips == 0)
        {
            UE_LOG(BaseWeaponLog, Warning, TEXT("No more clips"));
            return;
        }
        CurrentAmmo.Clips--;
    }
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    UE_LOG(BaseWeaponLog, Display, TEXT("---Change Clips---"));
}
bool AMGTBaseWeapon::CanReload() const
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}
void AMGTBaseWeapon::LogAmmo()
{
    FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + "/";
    AmmoInfo += CurrentAmmo.Infinite ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
    UE_LOG(BaseWeaponLog, Display, TEXT("%s"), *AmmoInfo);
}

bool AMGTBaseWeapon::IsAmmoFull() const
{
    return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

UNiagaraComponent* AMGTBaseWeapon::SpawnMuzzleFX()
{
    return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX,  //
        WeaponMesh,                                         //
        MuzzleSocketName,                                   //
        FVector::ZeroVector,                                //
        FRotator::ZeroRotator,                              //
        EAttachLocation::SnapToTarget,                      //
        true);
    
}
