// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DRINKWATER_API IInteractableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnInterAct(const AActor* OverlapActor);//需要执行交互的时候
	
	UFUNCTION(BlueprintNativeEvent)
	void OnFocus();//当射线检测到了可交互的物体
};
