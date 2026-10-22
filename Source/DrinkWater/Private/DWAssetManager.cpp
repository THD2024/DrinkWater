// Tian Handong


#include "DWAssetManager.h"
#include"DWGameplayTags.h"

UDWAssetManager& UDWAssetManager::Get()
{
	UDWAssetManager* DWAssetManager = Cast<UDWAssetManager>(GEngine->AssetManager);
	return *DWAssetManager;
}

void UDWAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FDwGameplayTags::InitializeGameplayTags();//在资产加载阶段初始化标签资产
}
