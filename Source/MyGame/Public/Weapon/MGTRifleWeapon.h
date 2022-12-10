// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/MGTBaseWeapon.h"
#include "MGTRifleWeapon.generated.h"

class UMGTWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class MYGAME_API AMGTRifleWeapon : public AMGTBaseWeapon
{
    GENERATED_BODY()

public:
    AMGTRifleWeapon();

    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TimeBetweenShots = 0.1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float BulletSpead = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 20.0f;

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    UMGTWeaponFXComponent* WeaponFXComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* TraceFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget";

    virtual void BeginPlay() override;
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
    FTimerHandle ShotTimerHandle;

    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent;

    void MakeDamage(const FHitResult& HitResult);
    void InitMuzzleFX();
    void SetMuzzleFXVisibility(bool Visible);
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);

    AController* GetController() const;
};
