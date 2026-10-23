// Tian Handong


#include "Item/DWItem.h"

#include "IDetailTreeNode.h"
#include "BlueprintFunctionLibrary/DWBlueprintFunctionLibrary.h"


ADWItem::ADWItem()
{
	PrimaryActorTick.bCanEverTick = true;
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	//可见性通道遮挡，便于射线检测
	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility,ECR_Block);
	SetRootComponent(SphereCollision);
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetRenderInDepthPass(true);
	ItemMesh->SetCustomDepthStencilValue(1);
	
	
}

void ADWItem::SetPhysicalSimulation(bool CanPhysicalSimulate)
{
	if (!ItemMesh) return;
	ItemMesh->SetSimulatePhysics(CanPhysicalSimulate);
}

void ADWItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADWItem::OnInterAct_Implementation(const AActor* OverlapActor)//处理在交互时该物体要干什么
{
	//有动画就播放没有动画就走另一条交互
	UDWItemDataAsset*ItemDA = UDWBlueprintFunctionLibrary::GetItemDataAssetFromGameState(this);
	if (ItemDA)
	{
		FDWItemInfo ItemInfo = ItemDA->GetItemInfoByTag(IdentityTag);
		if (ItemInfo.ItemMontage)
		{
			//播放item的交互动画
			return;
		}
	}
	OwnInteractAnim();
}

void ADWItem::OnFocus_Implementation()
{
	ItemMesh->SetRenderCustomDepth(true);
}

void ADWItem::OnUnFocus_Implementation()
{
	ItemMesh->SetRenderCustomDepth(false);
}

void ADWItem::ItemOwnAction_Implementation()//处理的是拿在手上后该物体可以干什么
{
	StartItemOwnAction();//Item自身处理基本交互外的其他功能，比如手电筒拿在手上，然后开关
}

FGameplayTag ADWItem::GetTagFromItem_Implementation()
{
	return IdentityTag;
}

void ADWItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

