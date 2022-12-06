// MyGameTry, All Rights Reserved


#include "Animations/MGTAnimNotify.h"

void UMGTAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}