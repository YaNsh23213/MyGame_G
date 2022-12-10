// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Player/MGTBaseCharacter.h"
#include "MGTPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class MYGAME_API AMGTPlayerCharacter : public AMGTBaseCharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AMGTPlayerCharacter(const FObjectInitializer& ObjInit);

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    virtual void OnDeath() override;

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual bool IsRunning() const override;

private:
    bool WantsToRun = false;
    bool IsMovingFoaward = false;

    void MoveForward(float Amount);
    void MoveRight(float Amount);

    void OnStartRunning();
    void OnStopRunning();
};
