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
class UCharInteractAnimDataAsset;

DECLARE_MULTICAST_DELEGATE_TwoParams(FTriggerCueWidgetDelegate,bool,AActor*);

UENUM()
enum class EInteractState : uint8
{
	Empty,
	Unequiping,
	Equipping
};

UCLASS()
class DRINKWATER_API ADWCharacter : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	ADWCharacter();
	
	FTriggerCueWidgetDelegate OnTriggerCueWidget;
	
	void BegintoSwithAnim();
	
	void EndtoSwithBegin();

protected:
	virtual void BeginPlay() override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	void InitInfo() ;
	
	void EyeLookTrace();
	
	bool IsSocketOccpied();
	
	bool AddItem(const FItemBag& BagInfo);
	
	UFUNCTION(BlueprintImplementableEvent)
	void SwitchLinkLayerAnim();//时机在于交互蒙太奇播放完后
	
	UFUNCTION(BlueprintCallable)
	AActor* GetCurrentAttachActor();

	void BegintoInteract();
	
	void PlayBeginCharInteractAnim();//播放角色交互动画
	
	void PlayEndCharInteractAnim();//播放角色交互动画
	
	UPROPERTY()
	TObjectPtr<UDWAbilitySystemComponent> DwAbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UDWBagComponent> BagComponent;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAnimInstance> FirstPersonMeshAnimIns;
	
	UPROPERTY()
	TObjectPtr<AActor> CurrentItem;//表示当前手中拿的item
	
	UPROPERTY()
	TObjectPtr<AActor> LastFocusActor;//上一个被检测到的物体
	
	UPROPERTY()
	TObjectPtr<AActor> CurrentFocusActor;//当前被检测到的物体

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCharInteractAnimDataAsset> PlayerInterActAnimAsset;
	
	EInteractState InteractState = EInteractState::Empty;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
