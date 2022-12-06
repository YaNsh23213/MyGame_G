// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGTProjecttile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UMGTWeaponFXComponent;

UCLASS()
class MYGAME_API AMGTProjecttile : public AActor
{
    GENERATED_BODY()

public:
    AMGTProjecttile();

    void SetShorDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
    UPROPERTY(VisibleAnyWhere, Category = "Weapon")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnyWhere, Category = "Weapon")
    UProjectileMovementComponent* MovementComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageRadius = 200.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 50.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool DoFullDamage = false;

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    float LifeSeconds = 5.0f;

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    UMGTWeaponFXComponent* WeaponFXComponent;

    virtual void BeginPlay() override;

private:
    FVector ShotDirection;

    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
        const FHitResult& Hit);

    AController* GetController() const;
};
