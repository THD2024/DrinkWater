// Tian Handong


#include "Player/DWCharacter.h"
#include"Interaction/InteractableInterface.h"
#include "Player/DWPlayerState.h"


ADWCharacter::ADWCharacter()
{
	
}

void ADWCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitInfo();//单机情况下，只需要在beginplay中进行actorinfo。
}


UAbilitySystemComponent* ADWCharacter::GetAbilitySystemComponent() const
{
	if (DwAbilitySystemComponent)
	{
		return DwAbilitySystemComponent;
	}
	return nullptr;
}


void ADWCharacter::InitInfo()
{
	//获取到playerstate中的asc复制到当前character的asc。
	if (ADWPlayerState* DWPlayerState = GetPlayerState<ADWPlayerState>())
	{
		DwAbilitySystemComponent = DWPlayerState->GetDWAbilitySystemComponent();
		DwAbilitySystemComponent->InitAbilityActorInfo(DWPlayerState,this);
	}
}

void ADWCharacter::EyeLookTrace()
{
	//在这里面通过射线检测
	FVector EyeLocation = FVector();
	FRotator EyeRotation = FRotator();
	GetActorEyesViewPoint(EyeLocation,EyeRotation);
	
	//计算视线前多少米,实现方向乘以最远距离
	FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 500.f);
	
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, EyeLocation, TraceEnd, ECollisionChannel::ECC_Visibility);
	if (HitResult.GetActor() != nullptr && HitResult.GetActor()->Implements<UInteractableInterface>())
	{
		if (IsSocketOccpied())return;
		IInteractableInterface::Execute_OnInterAct(HitResult.GetActor(), this);
	}
}

bool ADWCharacter::IsSocketOccpied()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (auto& AttachActor :AttachedActors )
	{
		return AttachActor->GetAttachParentSocketName() == FName("GripPoint");
	}
	return false;
}


void ADWCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	EyeLookTrace();
	
}

void ADWCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

