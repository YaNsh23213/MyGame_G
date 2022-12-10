// MyGameTry, All Rights Reserved


#include "AI/MGTAICharacter.h"
#include "AI/MGTAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/MGTAIWeaponComponent.h"
#include "BrainComponent.h"

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
