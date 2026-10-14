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
		if (IsSocketOccpied())//插槽被占着就需要判断，没被占着就直接拿
		{
			//如果手中插槽满了，就需要判断此时物品能否收纳，不能就丢弃。然后在去拿新的东西。
			//最终判断标准只有一个，手中的是不是inventoryitem，是收纳，不然就丢弃
			if (CurrentItem && CurrentItem->ActorHasTag(FName("PAC")))
			{
				AddItem(CurrentItem);
				CurrentItem->Destroy();
				CurrentItem = nullptr;
			}
			else
			{
				//如果不是可收纳，就判断是不是可拾取的，这类直接扔掉
				if (CurrentItem && CurrentItem->ActorHasTag(FName("PNC")))
				{
					CurrentItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				}
			}
			//第三种情况就不需要管了，因为根本不会到手上来。直接交互就行了
		}
		IInteractableInterface::Execute_OnInterAct(HitResult.GetActor(), this);
	}
}

bool ADWCharacter::IsSocketOccpied()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (auto& AttachActor :AttachedActors )
	{
		if(AttachActor->GetAttachParentSocketName() == FName("GripPoint"))
		{
			CurrentItem = AttachActor;//更新
			return true;
		}
	}
	return false;
}

void ADWCharacter::AddItem( AActor* Item)
{
	if (ItemBag.Num() <= BagVolum)
	{
		ItemBag.Add(Item);
		GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Blue,TEXT("存入新东西"));

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Blue,TEXT("背包容量已达上限,无法存入背包"));
	}
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

