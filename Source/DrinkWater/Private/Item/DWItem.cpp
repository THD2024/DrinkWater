// Tian Handong


#include "Item/DWItem.h"

#include "IDetailTreeNode.h"


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

void ADWItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADWItem::OnInterAct_Implementation(const AActor* OverlapActor)
{
	//父类这里再看
	CabintOpenandClose();
}

void ADWItem::OnFocus_Implementation()
{
	ItemMesh->SetRenderCustomDepth(true);
}

void ADWItem::OnUnFocus_Implementation()
{
	ItemMesh->SetRenderCustomDepth(false);
}

void ADWItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

