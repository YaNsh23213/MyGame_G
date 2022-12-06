// MyGameTry, All Rights Reserved

#include "Weapon/MGTProjecttile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/MGTWeaponFXComponent.h"

AMGTProjecttile::AMGTProjecttile()
{

    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->bReturnMaterialOnMove = true;

    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 4000.0f;
    MovementComponent->ProjectileGravityScale = 0.3f;

    WeaponFXComponent = CreateDefaultSubobject<UMGTWeaponFXComponent>("WeaponComponent");
}
void AMGTProjecttile::BeginPlay()
{
    Super::BeginPlay();

    check(MovementComponent);
    check(CollisionComponent);
    check(WeaponFXComponent);

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &AMGTProjecttile::OnProjectileHit);
    SetLifeSpan(LifeSeconds);
}

void AMGTProjecttile::OnProjectileHit(
    UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!GetWorld()) return;

    MovementComponent->StopMovementImmediately();

    // make damage
    UGameplayStatics::ApplyRadialDamage(GetWorld(),  //
        DamageAmount,                                //
        GetActorLocation(),                          //
        DamageRadius,                                //
        UDamageType::StaticClass(),                  //
        {GetOwner()},                                //
        this,                                        //
        GetController(),                             //
        DoFullDamage);

    WeaponFXComponent->PlayImapctFX(Hit);
    Destroy();
}

AController* AMGTProjecttile::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}
