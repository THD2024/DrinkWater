// Tian Handong


#include "Data/AnimLayerDataAsset.h"

TSubclassOf<UDWAnimInstance> UAnimLayerDataAsset::GetRelevantAnimLayer(const FGameplayTag& InTag)
{
	for (const auto& AnimLayer : AnimLayerAsset)
	{
		if (InTag.MatchesTagExact(AnimLayer.Key))
		{
			return AnimLayer.Value;
		}
	}
	return nullptr;
}
