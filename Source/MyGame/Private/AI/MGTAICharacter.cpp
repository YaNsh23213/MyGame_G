// MyGameTry, All Rights Reserved

#include "AI/MGTAICharacter.h"
#include "AI/MGTAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/MGTAIWeaponComponent.h"
#include "BrainComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/MGTHealthBarWidget.h"
#include "Components/MGTHealthComponent.h"

AMGTAICharacter::AMGTAICharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UMGTAIWeaponComponent>("WeaponComponent"))
{
    AIControllerClass = AMGTAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::Disabled;

    bUseControllerRotationYaw = false;
    //
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void AMGTAICharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthWidgetComponent);
}

void AMGTAICharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateHelathWidgetVisibility();
}

void AMGTAICharacter::OnDeath()
{
    Super::OnDeath();
    const auto MGTCotroller = Cast<AAIController>(Controller);
    if (MGTCotroller && MGTCotroller->BrainComponent)
    {
        MGTCotroller->BrainComponent->Cleanup();
    }
}

void AMGTAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
    Super::OnHealthChanged(Health, HealthDelta);

    const auto HealthBarWidget = Cast<UMGTHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if (!HealthBarWidget) return;
    HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void AMGTAICharacter::UpdateHelathWidgetVisibility()
{
    if (!GetWorld() || !GetWorld()->GetFirstPlayerController() || !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()) return;
    const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
    const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
    HealthWidgetComponent->SetVisibility(Distance < HealtVisibilityDistance, true);
}