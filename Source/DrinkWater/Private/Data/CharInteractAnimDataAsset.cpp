// Tian Handong


#include "Data/CharInteractAnimDataAsset.h"

FCharInteractAnim UCharInteractAnimDataAsset::GetRelevantAnimAssetbyTag(const FGameplayTag& Tag) const
{
	for (const auto& AnimAsset : InteractAnimAssets)
	{
		if (AnimAsset.TypeTag.MatchesTagExact(Tag))
		{
			return AnimAsset;
		}
	}
	return FCharInteractAnim();//返回空结构体
}
