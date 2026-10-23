// Tian Handong


#include "Data/DWBagComponent.h"

UDWBagComponent::UDWBagComponent()
{
	
	PrimaryComponentTick.bCanEverTick = true;


}

bool UDWBagComponent::AddItemtoBag(const FItemBag& ItemBagInfo)
{
	if (Bag.Num() < 6)
	{
		Bag.Add(ItemBagInfo);
		GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Red,FString(TEXT("已存入")));

		return true;
	}
	GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Red,FString(TEXT("背包已满，无法存入")));
	return false;
}


void UDWBagComponent::BeginPlay()
{
	Super::BeginPlay();


	
}



void UDWBagComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


}

