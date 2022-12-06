// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MGTCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API UMGTCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

		public:
    virtual float GetMaxSpeed() const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement",meta=(ClampMin="1.5",ClampMax="10.0"))
    float RunModifier = 2.0f;
	
};
