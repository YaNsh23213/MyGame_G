// MyGameTry, All Rights Reserved

#include "Components/MGTWeaponComponent.h"
#include "Weapon/MGTBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/MGTEquipFinishedAnimNotify.h"
#include "Animations/MGTReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

constexpr static int32 WeaponNum = 2;

UMGTWeaponComponent::UMGTWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UMGTWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    checkf(WeaponData.Num() == WeaponNum, TEXT("Our character can only %i weapon items"), WeaponNum);

    CurrentWeaponIndex = 0;
    InitAnimations();
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}
void UMGTWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();
    Super::EndPlay(EndPlayReason);
}

void UMGTWeaponComponent::SpawnWeapons()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld()) return;

    for (auto OneWeaponData : WeaponData)
    {
        auto Weapon = GetWorld()->SpawnActor<AMGTBaseWeapon>(OneWeaponData.WeaponClass);
        if (!Weapon) return;

        Weapon->OnclipEmpty.AddUObject(this, &UMGTWeaponComponent::OnEmptyClip);
        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void UMGTWeaponComponent::AttachWeaponToSocket(AMGTBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if (!Weapon || !SceneComponent) return;
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}
void UMGTWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
    {
        UE_LOG(LogWeaponComponent, Warning, TEXT("Invalid weapon idnex"));
        return;
    }
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;
    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }
    CurrentWeapon = Weapons[WeaponIndex];
    // CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
    const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data) {  //
        return Data.WeaponClass == CurrentWeapon->GetClass();                                 //
    });
    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}
void UMGTWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    Character->PlayAnimMontage(Animation);
}
void UMGTWeaponComponent::InitAnimations()
{

    auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<UMGTEquipFinishedAnimNotify>(EquipAnimMontage);
    if (EquipFinishedNotify)
    {
        EquipFinishedNotify->OnNotified.AddUObject(this, &UMGTWeaponComponent::OnEquipFineshed);
    }
    else
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("Equip anim notify forgotten to set"));
        checkNoEntry();
    }
    for (auto OneWeaponData : WeaponData)
    {
        auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<UMGTReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
        {
            if (!ReloadFinishedNotify)
            {
                UE_LOG(LogWeaponComponent, Error, TEXT("Reload anim notify forgotten to set"));
                checkNoEntry();
            }
        }
        ReloadFinishedNotify->OnNotified.AddUObject(this, &UMGTWeaponComponent::OnReloadFineshed);
    }
}
void UMGTWeaponComponent::OnEquipFineshed(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComponent != Character->GetMesh()) return;
    EquipAnimInProgress = false;
}

void UMGTWeaponComponent::OnReloadFineshed(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComponent != Character->GetMesh()) return;
    ReloadAnimInProgress = false;
}

void UMGTWeaponComponent::StartFire()
{
    if (!CanFire()) return;
    CurrentWeapon->StartFire();
}
void UMGTWeaponComponent::StopFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

void UMGTWeaponComponent::NextWeapon()
{
    if (!CanEquip()) return;
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}
void UMGTWeaponComponent::Reload()
{
    ChangeClip();
}
bool UMGTWeaponComponent::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    if (CurrentWeapon)
    {
        UIData = CurrentWeapon->GetUIData();
        return true;
    }
    return false;
}
bool UMGTWeaponComponent::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    if (CurrentWeapon)
    {
        AmmoData = CurrentWeapon->GetAmmoData();
        return true;
    }
    return false;
}
bool UMGTWeaponComponent::TryToAddAmmo(TSubclassOf<AMGTBaseWeapon> WeapomType, int32 ClipsAmount)
{

    for (const auto Weapon : Weapons)
    {
        if (Weapon && Weapon->IsA(WeapomType))
        {
            return Weapon->TryToGetAmmo(ClipsAmount);
        }
    }
    return false;
}
bool UMGTWeaponComponent::CanFire() const
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UMGTWeaponComponent::CanReload() const
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress && CurrentWeapon->CanReload();
}

void UMGTWeaponComponent::OnEmptyClip(AMGTBaseWeapon* AmmoEmptyWeapon)
{
    if (!AmmoEmptyWeapon) return;
    if (CurrentWeapon == AmmoEmptyWeapon)
    {
        ChangeClip();
    }
    else
    {
        for (const auto Weapon : Weapons)
        {
            if (Weapon == AmmoEmptyWeapon)
            {
                Weapon->ChacgeClip();
            }
        }
    }
}

void UMGTWeaponComponent::ChangeClip()
{
    if (!CanReload()) return;
    CurrentWeapon->StopFire();
    CurrentWeapon->ChacgeClip();
    ReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}

bool UMGTWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress && !ReloadAnimInProgress;
}
bool UMGTWeaponComponent::NeedAmmo(TSubclassOf<AMGTBaseWeapon> WeapomType)
{

    for (const auto Weapon : Weapons)
    {
        if (Weapon && Weapon->IsA(WeapomType))
        {
            return !Weapon->IsAmmoFull();
        }
    }
    return false;
}