// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "UI/DWWidgeController.h"
#include "OverlayWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class DRINKWATER_API UOverlayWidgetController : public UDWWidgeController
{
	GENERATED_BODY()
public:
	virtual void BroadInitValue() override;
	
	virtual void BindCallBack() override;
};
