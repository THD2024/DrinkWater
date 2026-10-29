// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include"Animation/AnimMontage.h"
#include "CharInteractAnimDataAsset.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCharInteractAnim
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag TypeTag = FGameplayTag();//表示当前动画是对应的哪个item的交互动画
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> BeginInteractAnim = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> EndInteractAnim = nullptr;
};


UCLASS(BlueprintType,Blueprintable)
class DRINKWATER_API UCharInteractAnimDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	FCharInteractAnim GetRelevantAnimAssetbyTag(const FGameplayTag& Tag) const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FCharInteractAnim> InteractAnimAssets;
};
