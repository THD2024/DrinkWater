// Tian Handong


#include "Core/DWGameStateBase.h"

UDWItemDataAsset* ADWGameStateBase::GetItemDataAsset()
{
	if (ItemDataAsset)
	{
		return ItemDataAsset;
	}
	return nullptr;
}

UAnimLayerDataAsset* ADWGameStateBase::GetAnimLayerDataAsset()
{
	if (AnimLayerAsset)
	{
		return AnimLayerAsset;
	}
	return nullptr;
}
