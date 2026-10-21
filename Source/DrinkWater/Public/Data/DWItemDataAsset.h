// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DWItemDataAsset.generated.h"

/**
 * 
 */
 
 USTRUCT(BlueprintType,Blueprintable)
 struct FDWItemInfo
 {
	 GENERATED_BODY()
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	FName Name = FName("");
 	
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	FName Description = FName("");
 	
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	UTexture2D* ItemPhoto;
 	
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	TObjectPtr<UAnimMontage> ActorMontage;
 	
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	TObjectPtr<UAnimMontage> ItemMontage;
 	
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	FGameplayTag IdentityTag;
 };
 
UCLASS()
class DRINKWATER_API UDWItemDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
protected:
	TArray<FDWItemInfo> ItemInfos;
	
public:
	UFUNCTION(BlueprintCallable)
	FDWItemInfo GetItemInfoByTag(const FGameplayTag& Tag) const;
};
