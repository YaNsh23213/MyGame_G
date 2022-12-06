// MyGameTry, All Rights Reserved


#include "Components/MGTCharacterMovementComponent.h"
#include "Player/MGTBaseCharacter.h"

float UMGTCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const AMGTBaseCharacter* Player = Cast<AMGTBaseCharacter>(GetPawnOwner());
    return Player&&Player->IsRunning()? MaxSpeed * RunModifier:MaxSpeed;
}
