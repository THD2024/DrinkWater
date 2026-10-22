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
