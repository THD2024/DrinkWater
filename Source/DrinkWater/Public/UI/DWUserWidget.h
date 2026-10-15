// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DWUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DRINKWATER_API UDWUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnWidgetControllerSet();
	
	UPROPERTY(BlueprintReadOnly)
	UObject* WidgetController;
};
