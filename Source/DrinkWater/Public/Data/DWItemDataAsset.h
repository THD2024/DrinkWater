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
 struct FDWItemInfo//这里面存每个课交互的actor的基本信息，不添加设计难度
 {
	 GENERATED_BODY()
 	
 	FDWItemInfo() : Name(NAME_None),Description(NAME_None),ItemPhoto(nullptr),ItemBeginMontage(nullptr){}
 	
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	FName Name = FName("");
 	
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	FName Description = FName("");
 	
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	UTexture2D* ItemPhoto = nullptr;
 	
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	TObjectPtr<UAnimMontage> ItemBeginMontage = nullptr;//物体交互动画
 	
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	TObjectPtr<UAnimMontage> ItemEndMontage = nullptr;//物体交互动画
 	
 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
 	FGameplayTag IdentityTag;
 };
 
UCLASS(Blueprintable,BlueprintType)
class DRINKWATER_API UDWItemDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FDWItemInfo> ItemInfos;
	
public:
	UFUNCTION(BlueprintCallable)
	FDWItemInfo GetItemInfoByTag(const FGameplayTag& Tag) const;
};
