// MyGameTry, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGTBasePickup.generated.h"

class USphereComponent;

UCLASS()
class MYGAME_API AMGTBasePickup : public AActor
{
    GENERATED_BODY()

public:
    AMGTBasePickup();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;

    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
    virtual void Tick(float DeltaTime) override;
    bool CouldBeTaken() const;

private:
    float RotationYaw = 0.0f;
    FTimerHandle RespawnTimerHandle;

    void PickupWasTaken();
    void Respawn();
    virtual bool GivePickupTo(APawn* PlayerPawn);

    void GenerateRotationYaw();
};
