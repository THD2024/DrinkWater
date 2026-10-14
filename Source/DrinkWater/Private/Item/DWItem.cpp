// Tian Handong


#include "Item/DWItem.h"




ADWItem::ADWItem()
{
	PrimaryActorTick.bCanEverTick = true;
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	//可见性通道遮挡，便于射线检测
	SphereCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility,ECR_Block);
	SetRootComponent(SphereCollision);
	
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
	ItemMesh->SetupAttachment(RootComponent);
	
	
}

void ADWItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADWItem::OnInterAct_Implementation(const AActor* OverlapActor)
{
	//父类这里再看
	
}

void ADWItem::OnFocus_Implementation()
{
	//这里写统一的物体高亮逻辑,暂时先不管
}

void ADWItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

