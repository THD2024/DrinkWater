// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimInstance.h"
#include "DWAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class DRINKWATER_API UDWAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	const FGameplayTag& GetItemLinkedTag(){return ItemLinkedTag;}
	
protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FGameplayTag ItemLinkedTag = FGameplayTag();
};
