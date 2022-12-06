// MyGameTry, All Rights Reserved

#include "Weapon/Components/MGTWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

UMGTWeaponFXComponent::UMGTWeaponFXComponent()
{

    PrimaryComponentTick.bCanEverTick = false;
}

void UMGTWeaponFXComponent::PlayImapctFX(const FHitResult& Hit)
{
    auto ImpactData = DefaultImpactData;

    if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if (ImpactDataMap.Contains(PhysMat))
        {
            ImpactData = ImpactDataMap[PhysMat];
        }
    }

    // niagara
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),  //
        ImpactData.NiagaraEffect,                               //
        Hit.ImpactPoint,                                        //
        Hit.ImpactNormal.Rotation());

    // decal

    auto DeacalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),  //
        ImpactData.DecalData.Material,                  //
        ImpactData.DecalData.Size,                      //
        Hit.ImpactPoint,                                //
        Hit.ImpactNormal.Rotation());

    if (DeacalComponent)
    {
        DeacalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeTime);
    }

}
