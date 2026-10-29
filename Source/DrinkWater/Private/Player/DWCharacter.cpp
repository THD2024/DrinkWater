// Tian Handong


#include "Player/DWCharacter.h"
#include "DWGameplayTags.h"
#include "BlueprintFunctionLibrary/DWBlueprintFunctionLibrary.h"
#include "Data/CharInteractAnimDataAsset.h"
#include"Interaction/InteractableInterface.h"
#include "Player/DWPlayerController.h"
#include "Player/DWPlayerState.h"
#include "UI/DWHUD.h"


ADWCharacter::ADWCharacter()
{
	BagComponent = CreateDefaultSubobject<UDWBagComponent>("BagComponent");
}

void ADWCharacter::TimetoSwithAnim()
{
	SwitchLinkLayerAnim();//动画通知后，此时可以进行切换，
	
}

void ADWCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitInfo();//单机情况下，只需要在beginplay中进行actorinfo。
	if (ADWPlayerController* PC = Cast<ADWPlayerController>(GetController()))
	{
		PC->OnInteract.AddUObject(this, &ADWCharacter::BegintoInteract);
	}
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
		
		if (ADWPlayerController* PC = Cast<ADWPlayerController>(GetController()))
		{
			if (PC->GetHUD())
			{
				if (ADWHUD* HUD = Cast<ADWHUD>(PC->GetHUD()))
				{
					HUD->InitOverlay(PC,DWPlayerState);
				}
			}
		}
	}
	
}

void ADWCharacter::EyeLookTrace()//这个函数从现在开始只用来检测，不参与拾取逻辑。
{
	//在这里面通过射线检测
	FVector EyeLocation = FVector();
	FRotator EyeRotation = FRotator();
	GetActorEyesViewPoint(EyeLocation,EyeRotation);
	
	//计算视线前多少米,实现方向乘以最远距离
	FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 500.f);
	
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, EyeLocation, TraceEnd, ECollisionChannel::ECC_Visibility);
	if (HitResult.GetActor() != nullptr && Cast<ADWItem>(HitResult.GetActor()))//判断当前是不是检测到了东西，并且检测到的东西是不是可交互父类
	{
		CurrentFocusActor = HitResult.GetActor();//存储当前检测到的物体变量
		//这里面还需要连接到ui，用来提醒可以交互,通过广播
		OnTriggerCueWidget.Broadcast(true,CurrentFocusActor);
		if (LastFocusActor == CurrentFocusActor) return;//保证不会对一个物体重复高亮,这种情况一般表示当前每帧检测，视线还是在一个物体上面，或者根本没看物体
		if (CurrentFocusActor->Implements<UInteractableInterface>())
		{
			IInteractableInterface::Execute_OnFocus(CurrentFocusActor);
			if (LastFocusActor && LastFocusActor->Implements<UInteractableInterface>())
			{
				IInteractableInterface::Execute_OnUnFocus(LastFocusActor);//让前一个高亮解除

			}
		}
		LastFocusActor = CurrentFocusActor;//更新上一个看到的物体的值.而且这个条件保证当前只有当二者对象不一样的时候才
	}
	else
	{
		if (CurrentFocusActor && CurrentFocusActor->Implements<UInteractableInterface>())
		{
			IInteractableInterface::Execute_OnUnFocus(CurrentFocusActor);
		}
		CurrentFocusActor = nullptr;
		LastFocusActor = CurrentFocusActor;//此时要么没有检测到东西要么东西不是可交互的，在结尾更新这个
		OnTriggerCueWidget.Broadcast(false,CurrentFocusActor);
		
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

bool ADWCharacter::AddItem(const FItemBag& BagInfo)
{
	//这里播放收纳动画
	return BagComponent->AddItemtoBag(BagInfo);
}

AActor* ADWCharacter::GetCurrentAttachActor()
{//局限性，只能考虑在单手情况下， 双手情况下等做出了打火机，在在此基础上进行适配
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors);
	for (auto& AttachActor :AttachedActors )
	{
		if(AttachActor->GetAttachParentSocketName() == FName("GripPoint"))
		{
			return AttachActor;
		}
	}
	return nullptr;
}

void ADWCharacter::HandleItemOwnAction()
{
	if (CurrentFocusActor == nullptr)
	{
		IInteractableInterface::Execute_ItemOwnAction(CurrentItem);
		return;
	}
}

void ADWCharacter::BegintoInteract()
{
	//该函数绑定到按键回调，在这里面进行交互逻辑
	if (IsSocketOccpied())//插槽被占着就需要判断，没被占着就直接拿
	{
		//如果此时手中有，且视线没在可交互物体上，那么按e就是执行物体本身的操作
		if (CurrentFocusActor == nullptr)
		{
			IInteractableInterface::Execute_ItemOwnAction(CurrentItem);
			return;
		}
		//如果手中插槽满了，就需要判断此时物品能否收纳，不能就丢弃。然后在去拿新的东西。
		//最终判断标准只有一个，手中的是不是inventoryitem，是收纳，不然就丢弃
		if (CurrentItem && CurrentItem->ActorHasTag(FName("PAC")))
		{
			if (CurrentItem->Implements<UInteractableInterface>())
			{
				FGameplayTag IdentityTag = IInteractableInterface::Execute_GetTagFromItem(CurrentItem);
				if (!UDWBlueprintFunctionLibrary::GetItemDataAssetFromGameState(this))return;
				FDWItemInfo Iteminfo = UDWBlueprintFunctionLibrary::GetItemDataAssetFromGameState(this)->GetItemInfoByTag(IdentityTag);
				if (!Iteminfo.Name.IsValid() || !Iteminfo.ItemPhoto)return;//如果名字是空,图片是空，那就说明返回的是个空的info，就不存，反之存.虽然这种情况逻辑上不存在，但是以防万一
				FItemBag BagInfo(Iteminfo.Name,Iteminfo.ItemPhoto);
				if (AddItem(BagInfo))//如果添加完成就可以将currentitme重置了。
				{
					//现在背包里面存的是数据，存好后直接将当前世界中的actor销毁
					CurrentItem->Destroy();
					CurrentItem = nullptr;
				}
				else//当包满后，无法存入，就需要将手中的东西给扔掉，然后在拾取地上的新东西	
				{
					CurrentItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
					CurrentItem = nullptr;
				}
			}
			
		}
		else
		{
			//如果不是可收纳，就判断是不是可拾取的，这类直接扔掉
			if (CurrentItem && CurrentItem->ActorHasTag(FName("PNC")))
			{
				CurrentItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				//丢掉后添加物理特性，掉在地上
				if (CurrentItem->Implements<UInteractableInterface>())
				{
					//丢弃动画也可以在这里播放
					IInteractableInterface::Execute_SetItemPhysic(CurrentItem,true);
					CurrentItem = nullptr;//掉在地上不符合currentitem的定义，那么此时重置currentitem
				}
			}
		}
		//第三种情况就不需要管了，因为根本不会到手上来。直接交互就行了
		//现在要考虑如果此时实现对准的是先前掉落的物体，那么就需要关闭物理模拟
		if (CurrentFocusActor->Implements<UInteractableInterface>())
		{
			IInteractableInterface::Execute_SetItemPhysic(CurrentFocusActor,false);
		}
	}
	//证明手中没东西，那么就需要拿起来
	if (CurrentFocusActor == nullptr ||!CurrentFocusActor->Implements<UInteractableInterface>())return;//没有检测到物体或者物体没有继承接口
	//在这里可以播放角色的交互动画，根据当前的currentfocusactor来播放对应的交互动画
	FGameplayTag ItemTag = IInteractableInterface::Execute_GetTagFromItem(CurrentFocusActor);
	PlayBeginCharInteractAnim(ItemTag);
	IInteractableInterface::Execute_OnInterAct(CurrentFocusActor,this,this);
	// SwitchLinkLayerAnim();//只需要有了交互操作，那么这个时候就直接切换动画，在蓝图中控制玩家重复按交互键导致的动画无效切换的漏洞
	//这里已知不会触发的边界情况：当玩家手里有东西，视线不对向可交互物体，此时按e会在上面第一种情况被处理。当玩家什么都没有但是按e会被上面处理，交互都不会执行
	//这里需要注意的情况，当交互的物体是不能拿在手中的，此时会将手中的东西丢弃或者收纳，那么就需要进行动画需要切换会原来的空手动画。
}

void ADWCharacter::PlayBeginCharInteractAnim(const FGameplayTag& TypeTag)
{
	FCharInteractAnim AnimAsset = PlayerInterActAnimAsset->GetRelevantAnimAssetbyTag(TypeTag);
	if (AnimAsset.BeginInteractAnim && FirstPersonMeshAnimIns)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *GetNameSafe(AnimAsset.BeginInteractAnim));
		FirstPersonMeshAnimIns->Montage_Play(AnimAsset.BeginInteractAnim,1.f);
	}
}

void ADWCharacter::PlayEndCharInteractAnim(const FGameplayTag& TypeTag)
{
	if (!PlayerInterActAnimAsset)return;
	const FCharInteractAnim AnimAsset = PlayerInterActAnimAsset->GetRelevantAnimAssetbyTag(TypeTag);
	if (AnimAsset.EndInteractAnim && FirstPersonMeshAnimIns)
	{
		FirstPersonMeshAnimIns->Montage_Play(AnimAsset.EndInteractAnim,1.f);
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

