// Tian Handong


#include "Item/DWItem.h"




ADWItem::ADWItem()
{
	PrimaryActorTick.bCanEverTick = true;
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(SphereCollision);
	
	ItemMesh = CreateDefaultSubobject<USkeletalMeshComponent>("ItemMesh");
	ItemMesh->SetupAttachment(RootComponent);
	
	
}

void ADWItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADWItem::OnInterAct_Implementation(const AActor* OverlapActor)
{
	//测试阶段
	if (OverlapActor == nullptr)return;
	SetActorEnableCollision(false);
	USkeletalMeshComponent* Mesh = OverlapActor->FindComponentByTag<USkeletalMeshComponent>(FName("FirstPersonMesh"));
	if (Mesh == nullptr)return;
	FAttachmentTransformRules TransformRules = FAttachmentTransformRules::SnapToTargetIncludingScale;
	AttachToComponent(Mesh,TransformRules,SocketName);
}

void ADWItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

