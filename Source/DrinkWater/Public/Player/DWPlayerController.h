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
	void HandleRun(const FInputActionValue& Value);
	void HandleRunEnd(const FInputActionValue& Value);
	
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
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> Run;
	
	UPROPERTY(EditDefaultsOnly)
	float MoveSensitivity = 1.f;
	
	UPROPERTY(EditDefaultsOnly)
	float PlayerMaxWalkSpeed = 300.f;
	
	UPROPERTY(EditDefaultsOnly)
	float PlayerNormalWalkSpeed = 300.f;
};
