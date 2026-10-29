// Tian Handong


#include "Item/DWPickupItem.h"


ADWPickupItem::ADWPickupItem()
{
	Tags.Add(FName("PNC"));
}

void ADWPickupItem::OnInterAct_Implementation(const AActor* OverlapActor,const ACharacter* OwnerPlayer)
{
	//写自己单独的逻辑，直接拿到手里去
	if (OverlapActor == nullptr)return;
	SetActorEnableCollision(false);
	USkeletalMeshComponent* Mesh = OverlapActor->FindComponentByTag<USkeletalMeshComponent>(FName("FirstPersonMesh"));
	if (Mesh == nullptr)return;
	FAttachmentTransformRules TransformRules = FAttachmentTransformRules::SnapToTargetIncludingScale;
	AttachToComponent(Mesh,TransformRules,SocketName);
	//播放对应的拾取动画,比如手电筒慢慢抬起
	PlayAnimFromItemAsset(OwnerPlayer);
}

void ADWPickupItem::SetItemPhysic_Implementation(bool CanPhysical)
{
	SetPhysicalSimulation(CanPhysical);
}


