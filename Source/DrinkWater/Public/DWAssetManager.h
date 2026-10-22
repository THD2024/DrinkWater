// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "DWAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class DRINKWATER_API UDWAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UDWAssetManager& Get(); 
	
	virtual void StartInitialLoading() override;
};
