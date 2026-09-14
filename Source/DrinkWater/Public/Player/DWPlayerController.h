// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "DWPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DRINKWATER_API ADWPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	ADWPlayerController();
	
protected:
	
	virtual void BeginPlay() override;
	
	virtual void AcknowledgePossession(class APawn* P) override;
	
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> DWContext;
};
