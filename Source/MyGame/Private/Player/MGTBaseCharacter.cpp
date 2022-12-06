// MyGameTry, All Rights Reserved

#include "Player/MGTBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
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
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateAbstractDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.0f, 0.0f, 80.0f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<UMGTHealthComponent>("HealthComponent");

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());
    HealthTextComponent->SetOwnerNoSee(true);

    WeaponComponent = CreateDefaultSubobject<UMGTWeaponComponent>("WeaponComponent");
}

void AMGTBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(HealthTextComponent);
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

// Called to bind functionality to input
void AMGTBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    check(WeaponComponent);


    PlayerInputComponent->BindAxis("MoveForward", this, &AMGTBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AMGTBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &AMGTBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &AMGTBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMGTBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AMGTBaseCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &AMGTBaseCharacter::OnStopRunning);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UMGTWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UMGTWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UMGTWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UMGTWeaponComponent::Reload);
}

void AMGTBaseCharacter::MoveForward(float Amount)
{
    if (Amount == 0.0f) return;
    IsMovingFoaward = Amount > 0.0f;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void AMGTBaseCharacter::MoveRight(float Amount)
{
    if (Amount == 0.0f) return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void AMGTBaseCharacter::OnStartRunning()
{
    WantsToRun = true;
}

void AMGTBaseCharacter::OnStopRunning()
{
    WantsToRun = false;
}

bool AMGTBaseCharacter::IsRunning() const
{
    return WantsToRun && IsMovingFoaward && !GetVelocity().IsZero();
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
    //PlayAnimMontage(DeathAnimMontage);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.0f);
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}

void AMGTBaseCharacter::OnHealthChanged(float Health, float HealtDealta)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
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
