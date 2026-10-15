// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DWWidgeController.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FDWWidgeControllerParams
{
	GENERATED_BODY()

public:
	FDWWidgeControllerParams(){};
	
	FDWWidgeControllerParams(APlayerController* PlayerController, APlayerState* PlayerState) : PC(PlayerController), PS(PlayerState){}
	
	UPROPERTY()
	TObjectPtr<APlayerController> PC;
	
	UPROPERTY()
	TObjectPtr<APlayerState> PS;
	
};

UCLASS(Blueprintable, BlueprintType)
class DRINKWATER_API UDWWidgeController : public UObject
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APlayerController> PC;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<APlayerState> PS;
	
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FDWWidgeControllerParams& params);
	
	UFUNCTION(BlueprintCallable)
	virtual void BroadInitValue();
	
	UFUNCTION(BlueprintCallable)
	virtual void BindCallBack();
};
