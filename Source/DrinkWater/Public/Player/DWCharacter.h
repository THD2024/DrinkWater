// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Core/DWAbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "Item/DWInventoryItem.h"
#include "DWCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

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
	
	void EyeLookTrace();
	
	bool IsSocketOccpied();
	
	void AddItem(AActor* Item);
	
	UPROPERTY()
	TObjectPtr<UDWAbilitySystemComponent> DwAbilitySystemComponent;
	
	UPROPERTY()
	TArray<TObjectPtr<AActor>> ItemBag;//测试暂用
	
	UPROPERTY(EditDefaultsOnly)
	int32 BagVolum = 6;//背包容量
	
	UPROPERTY()
	TObjectPtr<AActor> CurrentItem;//表示当前手中拿的item


public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
