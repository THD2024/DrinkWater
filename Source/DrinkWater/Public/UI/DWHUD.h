// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "CueWidgeController.h"
#include "DWUserWidget.h"
#include "OverlayWidgetController.h"
#include "GameFramework/HUD.h"
#include "DWHUD.generated.h"

/**
 * 
 */
UCLASS()
class DRINKWATER_API ADWHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	void InitOverlay(APlayerController* PC, APlayerState* PS);
	
	UFUNCTION(BlueprintCallable)
	UCueWidgeController* GetCueWidgeController(const FDWWidgeControllerParams& params);
	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UDWUserWidget> OverlayWidget;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UCueWidgeController> CueWidgeController;
	
	UOverlayWidgetController* GetOverlayWidgetController(const FDWWidgeControllerParams& params);
	
	

	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDWUserWidget> OverlayWidgetClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCueWidgeController> CueWidgetControllerClass;
 	
	
};
