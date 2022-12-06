// MyGameTry, All Rights Reserved


#include "Pickups/MGTBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

AMGTBasePickup::AMGTBasePickup()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

    SetRootComponent(CollisionComponent);

}


void AMGTBasePickup::BeginPlay()
{
	Super::BeginPlay();



    check(CollisionComponent);

    GenerateRotationYaw();
	
}

void AMGTBasePickup::NotifyActorBeginOverlap(AActor* OtherActor) 
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if (GivePickupTo(Pawn))
    {
        PickupWasTaken();
    }
}


void AMGTBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
}

void AMGTBasePickup::PickupWasTaken() 
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(false, true);
    }
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AMGTBasePickup::Respawn, RespawnTime);
}

void AMGTBasePickup::Respawn() 
{
    GenerateRotationYaw();
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(true, true);
    }
}

bool AMGTBasePickup::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void AMGTBasePickup::GenerateRotationYaw() 
{
    const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
    RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}

 bool AMGTBasePickup::CouldBeTaken() const 
 {
     return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
 }

