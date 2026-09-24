// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Camera/CameraComponent.h"
#include "Core/DWAbilitySystemComponent.h"
#include "GameFramework/Character.h"

#include "DWCharacter.generated.h"

UCLASS()
class DRINKWATER_API ADWCharacter : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	ADWCharacter();

	void ExecutePhysicalJump();
	
	bool GetJumpStatus(){return IsJumpStarting;}
	
	UFUNCTION(BlueprintCallable)
	void SetJumpingStatus(bool InIsJumpStarting){ IsJumpStarting = InIsJumpStarting; }
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> JumpMontage;
	
	
	
protected:
	virtual void BeginPlay() override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	void InitInfo() ;
	
	UPROPERTY()
	TObjectPtr<UDWAbilitySystemComponent> DwAbilitySystemComponent;
	
	UPROPERTY(BlueprintReadWrite)
	bool IsJumpStarting = false;
	
	
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
};
