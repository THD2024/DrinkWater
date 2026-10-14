// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "Item/DWPickupItem.h"
#include "DWInventoryItem.generated.h"

/**
 * 
 */
UCLASS()
class DRINKWATER_API ADWInventoryItem : public ADWPickupItem
{//这里的区别在于可以拾取可存储
	GENERATED_BODY()
	
public:
	ADWInventoryItem();
};
