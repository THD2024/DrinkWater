// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Player/DWAnimInstance.h"
#include "AnimLayerDataAsset.generated.h"

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class DRINKWATER_API UAnimLayerDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	TSubclassOf<UDWAnimInstance> GetRelevantAnimLayer(const FGameplayTag& InTag);
	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TMap<FGameplayTag,TSubclassOf<UDWAnimInstance>> AnimLayerAsset;
	
	
};
