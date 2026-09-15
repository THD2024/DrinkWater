// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Core/DWAbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "DWCharacter.generated.h"

UCLASS()
class DRINKWATER_API ADWCharacter : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	ADWCharacter();

protected:
	virtual void BeginPlay() override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	void InitInfo() ;
	
	UPROPERTY()
	TObjectPtr<UDWAbilitySystemComponent> DwAbilitySystemComponent;
	
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
