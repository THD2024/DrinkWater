// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "UI/DWWidgeController.h"
#include "CueWidgeController.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInteractWidgetDelegate,bool,InCanTrigger,AActor*,DetectedActor);

UCLASS()
class DRINKWATER_API UCueWidgeController : public UDWWidgeController
{
	GENERATED_BODY()
	
public:
	
	virtual void BindCallBack() override;
	
	virtual void BroadInitValue() override;
	
protected:
	void TriggerCueWidget(bool CanTrigger,AActor* DetectedActor);
	
	UPROPERTY(BlueprintAssignable)
	FInteractWidgetDelegate TriggerDelegate;

};
