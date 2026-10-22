// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "Data/DWItemDataAsset.h"
#include "GameFramework/GameStateBase.h"
#include "DWGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class DRINKWATER_API ADWGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	UDWItemDataAsset* GetItemDataAsset();
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDWItemDataAsset> ItemDataAsset;
};
