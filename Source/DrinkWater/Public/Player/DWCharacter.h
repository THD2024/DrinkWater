// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Core/DWAbilitySystemComponent.h"
#include "Data/DWBagComponent.h"
#include "GameFramework/Character.h"
#include "DWCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

DECLARE_MULTICAST_DELEGATE_TwoParams(FTriggerCueWidgetDelegate,bool,AActor*);

UCLASS()
class DRINKWATER_API ADWCharacter : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	ADWCharacter();
	
	FTriggerCueWidgetDelegate OnTriggerCueWidget;

protected:
	virtual void BeginPlay() override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	void InitInfo() ;
	
	void EyeLookTrace();
	
	bool IsSocketOccpied();
	
	bool AddItem(const FItemBag& BagInfo);
	
	UFUNCTION(BlueprintImplementableEvent)
	void SwitchLinkLayerAnim();//时机在于当手中只要有东西就行了
	
	UFUNCTION(BlueprintCallable)
	AActor* GetCurrentAttachActor();
	
	void HandleItemOwnAction();

	void BegintoInteract();
	
	UPROPERTY()
	TObjectPtr<UDWAbilitySystemComponent> DwAbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UDWBagComponent> BagComponent;
	
	UPROPERTY()
	TObjectPtr<AActor> CurrentItem;//表示当前手中拿的item
	
	UPROPERTY()
	TObjectPtr<AActor> LastFocusActor;//上一个被检测到的物体
	
	UPROPERTY()
	TObjectPtr<AActor> CurrentFocusActor;//当前被检测到的物体

	

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
