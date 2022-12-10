// MyGameTry, All Rights Reserved

#include "Player/MGTBaseCharacter.h"
#include "Components/MGTCharacterMovementComponent.h"
#include "Components/MGTHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/MGTWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

// dwSets default values
AMGTBaseCharacter::AMGTBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UMGTCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    PrimaryActorTick.bCanEverTick = true;
    HealthComponent = CreateDefaultSubobject<UMGTHealthComponent>("HealthComponent");
    WeaponComponent = CreateDefaultSubobject<UMGTWeaponComponent>("WeaponComponent");
}

void AMGTBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(GetCharacterMovement());
    check(GetMesh());

    OnHealthChanged(HealthComponent->GetHealth(),0.0f);
    HealthComponent->OnDeath.AddUObject(this, &AMGTBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &AMGTBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &AMGTBaseCharacter::OnGroundLanded);
}

// Called every frame
void AMGTBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
bool AMGTBaseCharacter::IsRunning() const
{
    return false;
}

float AMGTBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) return 0.0f;
    const auto VelosityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelosityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelosityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void AMGTBaseCharacter::OnDeath()
{
    UE_LOG(BaseCharacterLog, Display, TEXT("pLAYER %s is dead"), *GetName());
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.0f);
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}

void AMGTBaseCharacter::OnHealthChanged(float Health, float HealtDealta)
{
    
}

void AMGTBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    const auto FallVelocityZ = -GetVelocity().Z;
    UE_LOG(BaseCharacterLog, Display, TEXT("On landed: %f"), FallVelocityZ);

    if (FallVelocityZ < LandedDamageVelocity.X) return;

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    UE_LOG(BaseCharacterLog, Display, TEXT("Final damage: %f"), FinalDamage);
    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void AMGTBaseCharacter::SetPlayerColor(const FLinearColor& Color)
{
    const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if (!MaterialInst) return;

    MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}
