// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Core/DWAbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "DWCharacter.generated.h"

UENUM(BlueprintType)
enum class ETurnType : uint8
{
	None,
	Turn90Left,
	Turn90Right,
	Turn180Left,
	Turn180Right
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTurnDeterminedDelegate, ETurnType);

UCLASS()
class DRINKWATER_API ADWCharacter : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	ADWCharacter();
	
	UFUNCTION(BlueprintCallable)
	void ExecutePhysicalJump();
	
	bool GetJumpStatus(){return IsJumpStarting;}
	
	UFUNCTION(BlueprintCallable)
	void SetJumpingStatus(bool InIsJumpStarting){ IsJumpStarting = InIsJumpStarting; }
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> JumpMontage;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> Right90Montage;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> Left90Montage;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> Right180Montage;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> Left180Montage;
	
	UPROPERTY(Transient)
	TObjectPtr<UAnimMontage> CurrentMontage = nullptr;//当前播放的动画蒙太奇
	
	
protected:
	virtual void BeginPlay() override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual void FaceRotation(FRotator NewControlRotation, float DeltaTime = 0) override;
	
	void InitInfo() ;
	
	void DetermineTurnType();
	
	void PlayTurnAnimation(ETurnType InTurnType);
	
	static bool SampleBoneComponentSpaceYaw(
	const UAnimSequence* Sequence,
	float SequenceTime,
	FName BoneName,
	float& OutYaw);
	
	UFUNCTION(BlueprintCallable, Category = "Animation|Turn")
	bool GetCurrentTurnRootAnimYaw(float& OutYaw,FName BoneName);
	
	UPROPERTY()
	TObjectPtr<UDWAbilitySystemComponent> DwAbilitySystemComponent;
	
	UPROPERTY(BlueprintReadWrite, Category = "Turn In Place")
	bool IsJumpStarting = false;
	
	UPROPERTY(BlueprintReadOnly, Category = "Turn In Place")
	bool IsInPlacing = false;
	
	UPROPERTY(BlueprintReadOnly, Category = "Turn In Place")
	bool bIsTurning = false;
	
	UPROPERTY(BlueprintReadOnly, Category = "Turn In Place")
	float TurnAngle = 0.0f;
	
	UPROPERTY(BlueprintReadWrite, Category = "Turn In Place")
	float TurnOffset = 0.f;//计算旋转差值（actor和controller之间的旋转差值）
	
	UPROPERTY(BlueprintReadWrite, Category = "Turn In Place")
	float CurrentAnimRotation = 0.0f;
	
	UPROPERTY(BlueprintReadWrite, Category = "Turn In Place")
	float LastAnimRotation = 0.0f;
	
	UPROPERTY(BlueprintReadWrite, Category = "Turn In Place")
	float AnimOffset = 0.0f;
	
	UPROPERTY(BlueprintReadOnly, Category = "Turn In Place")
	ETurnType TurnType = ETurnType::None;//初始化为none
	
	FOnTurnDeterminedDelegate OnTurnDetermined;
	
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

};
