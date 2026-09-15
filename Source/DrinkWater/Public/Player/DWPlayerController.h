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
	
	/*Movement*/
	void HandleMove(const FInputActionValue& Value);
	void HandleJump(const FInputActionValue& Value);
	void HandleCrouch(const FInputActionValue& Value);
	void HandleLook(const FInputActionValue& Value);
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> DWContext;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> Move;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> Jump;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> Crouch;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> Look;
};
