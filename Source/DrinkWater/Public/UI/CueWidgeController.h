// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "UI/DWWidgeController.h"
#include "CueWidgeController.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractWidgetDelegate,bool,InCanTrigger);

UCLASS()
class DRINKWATER_API UCueWidgeController : public UDWWidgeController
{
	GENERATED_BODY()
	
public:
	
	virtual void BindCallBack() override;
	
	virtual void BroadInitValue() override;
	
protected:
	void TriggerCueWidget(bool CanTrigger);
	
	UPROPERTY(BlueprintAssignable)
	FInteractWidgetDelegate TriggerDelegate;

};
