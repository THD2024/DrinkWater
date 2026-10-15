// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "DWPlayerController.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FInterActDelegate);

UCLASS()
class DRINKWATER_API ADWPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	ADWPlayerController();
	
	UPROPERTY(EditDefaultsOnly)
	float RunSpeed = 500.f;
	
	UPROPERTY(EditDefaultsOnly)
	float WalkSpeed = 300.f;
	
	FInterActDelegate OnInteract;
	
protected:
	
	virtual void BeginPlay() override;
	
	virtual void AcknowledgePossession(class APawn* P) override;
	
	virtual void SetupInputComponent() override;
	
	/*Movement*/
	
	UFUNCTION()
	void HandleCrouch(const FInputActionValue& Value);
	
	UFUNCTION()
	void HandleRun(const FInputActionValue& Value);
	
	UFUNCTION()
	void HandleStopRun(const FInputActionValue& Value);
	
	UFUNCTION()
	void HandleInterAct(const FInputActionValue& Value);
	
	
	
private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputMappingContext> DWContext;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> Crouch;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> Run;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InterAct;
	
	bool bIsCouching = false;
};
