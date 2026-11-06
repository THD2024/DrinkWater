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
	
	void EndtoSwithBegin();//第一阶段动画触发，准备进入阶段的中转站

	

protected:
	virtual void BeginPlay() override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	void InitInfo() ;
	
	void EyeLookTrace();
	
	bool IsSocketOccpied();
	
	bool AddItem(const FItemBag& BagInfo);
	
	UFUNCTION(BlueprintImplementableEvent)
	void EndToUnbindAnimLayer(AActor* EndActor,bool CanDestory);
	
	UFUNCTION(BlueprintImplementableEvent)
	void SwitchLinkLayerAnim();//时机在于交互蒙太奇播放完后
	
	UFUNCTION(BlueprintImplementableEvent)
	void BeginToBindAnimLayer(AActor* BeginActor);
	
	UFUNCTION(BlueprintCallable)
	AActor* GetCurrentAttachActor();//不依赖于currentitem，而是获取当前手中的item

	void BegintoInteract();
	
	void PlayBeginCharInteractAnim();//播放角色交互动画
	
	void PlayEndCharInteractAnim();//播放角色交互动画
	
	USkeletalMeshComponent* GetFirstPersonMeshComponent();
	
	bool PlayAnim(UAnimMontage* AnimMontage,float PlayRate);
	
	void UpdateHeadBot(float DeltaTime);
	
	
	UPROPERTY()
	TObjectPtr<UDWAbilitySystemComponent> DwAbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UDWBagComponent> BagComponent;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UAnimInstance> FirstPersonMeshAnimIns;
	
	UPROPERTY(Transient)
	TObjectPtr<USkeletalMeshComponent> FirstMeshCom;
	
	UPROPERTY()
	TObjectPtr<AActor> InteractItem;//表示在playbegin开始时视线对准的物体.
	
	UPROPERTY()
	TObjectPtr<AActor> LastFocusActor;//上一个被检测到的物体
	
	UPROPERTY()
	TObjectPtr<AActor> CurrentFocusActor;//当前被检测到的物体

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UCharInteractAnimDataAsset> PlayerInterActAnimAsset;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraShakeBase> WalkShakeClass;
	
	UPROPERTY()
	TObjectPtr<UCameraShakeBase> WalkShake;
	
	EInteractState InteractState = EInteractState::Empty;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
};
