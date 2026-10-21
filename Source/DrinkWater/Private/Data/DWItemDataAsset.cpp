// Tian Handong


#include "Data/DWItemDataAsset.h"

FDWItemInfo UDWItemDataAsset::GetItemInfoByTag(const FGameplayTag& Tag) const
{
	for (auto& Info : ItemInfos)
	{
		if (Info.IdentityTag.MatchesTagExact(Tag))
		{
			return Info;
		}
	}
	return FDWItemInfo();
}
