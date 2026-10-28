// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "Data/AnimLayerDataAsset.h"
#include "Data/DWItemDataAsset.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DWBlueprintFunctionLibrary.generated.h"

class UCueWidgeController;
/**
 * 
 */
UCLASS()
class DRINKWATER_API UDWBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintPure,BlueprintCallable)
	static UCueWidgeController* GetCueWidgetController(const UObject* WorldContextObject, APlayerController* PlayerController);
	
	UFUNCTION(BlueprintPure,BlueprintCallable)
	static UDWItemDataAsset* GetItemDataAssetFromGameState(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure,BlueprintCallable)
	static UAnimLayerDataAsset* GetAnimLayerDataAssetFromGameState(const UObject* WorldContextObject);
};
