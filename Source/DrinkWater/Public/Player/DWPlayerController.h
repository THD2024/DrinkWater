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
	float SlowSpeed = 300.f;
	
	UPROPERTY(EditDefaultsOnly)
	float WalkSpeed = 600.f;
	
	FInterActDelegate OnInteract;
	
protected:
	
	virtual void BeginPlay() override;
	
	virtual void AcknowledgePossession(class APawn* P) override;
	
	virtual void SetupInputComponent() override;
	
	/*Movement*/
	
	UFUNCTION()
	void HandleCrouch(const FInputActionValue& Value);
	
	UFUNCTION()
	void HandleSlow(const FInputActionValue& Value);
	
	UFUNCTION()
	void HandleStopSlow(const FInputActionValue& Value);
	
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
