// Tian Handong


#include "DWGameplayTags.h"

#include "GameplayTagsManager.h"


void FDwGameplayTags::InitializeGameplayTags()
{
	//在这里添加新标签
	GameplayTags.Item_Type_Canbinet = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Item.Type.Canbinet"),FString(TEXT("a container")));
	GameplayTags.Item_Type_Banana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Item.Type.Banana"),FString(TEXT("Banana")));
	GameplayTags.Item_Type_Flashlight = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Item.Type.Flashlight"),FString(TEXT("Flashlight")));
}

FDwGameplayTags FDwGameplayTags::GameplayTags;//实例声明