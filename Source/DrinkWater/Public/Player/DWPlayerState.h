// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "Core/DWAbilitySystemComponent.h"
#include "GameFramework/PlayerState.h"
#include "DWPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DRINKWATER_API ADWPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ADWPlayerState();
	
	TObjectPtr<UDWAbilitySystemComponent> GetDWAbilitySystemComponent() ;
	
protected:
	
	UPROPERTY()
	TObjectPtr<UDWAbilitySystemComponent> DWAbilitySystemComponent;
};
