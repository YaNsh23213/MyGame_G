// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MGTCoreTypes.h"
#include "MGTWeaponComponent.generated.h"

class AMGTBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYGAME_API UMGTWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMGTWeaponComponent();

    virtual void StartFire();
    void StopFire();
    virtual void NextWeapon();
    void Reload();

    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

    bool TryToAddAmmo(TSubclassOf<AMGTBaseWeapon> WeapomType, int32 ClipsAmount);
    bool NeedAmmo(TSubclassOf<AMGTBaseWeapon> WeapomType);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSoket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage;

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UPROPERTY()
    AMGTBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<AMGTBaseWeapon*> Weapons;

    int32 CurrentWeaponIndex = 0;

    bool CanFire() const;
    bool CanEquip() const;

    void EquipWeapon(int32 WeaponIndex);

private:
    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;

    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;

    void SpawnWeapons();
    void AttachWeaponToSocket(AMGTBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);

    void PlayAnimMontage(UAnimMontage* Animation);
    void InitAnimations();
    void OnEquipFineshed(USkeletalMeshComponent* MeshComponent);
    void OnReloadFineshed(USkeletalMeshComponent* MeshComponent);

    bool CanReload() const;

    void OnEmptyClip(AMGTBaseWeapon* AmmoEmptyWeapon);
    void ChangeClip();
};
