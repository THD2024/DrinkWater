// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "DWUserWidget.h"
#include "GameFramework/HUD.h"
#include "DWHUD.generated.h"

/**
 * 
 */
UCLASS()
class DRINKWATER_API ADWHUD : public AHUD
{
	GENERATED_BODY()

	
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UDWUserWidget> OverlayWidget;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDWUserWidget> OverlayWidgetClass;
	
};
