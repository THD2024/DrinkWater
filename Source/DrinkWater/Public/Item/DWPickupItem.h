// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "Item/DWItem.h"
#include "DWPickupItem.generated.h"

/**
 * 
 */
UCLASS()
class DRINKWATER_API ADWPickupItem : public ADWItem
{//可拾取
	GENERATED_BODY()

public:
	ADWPickupItem();
	
	virtual void OnInterAct_Implementation(const AActor* OverlapActor) override;
	
	virtual void SetItemPhysic_Implementation(bool CanPhysical) override;
	

};
