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

void ADWCharacter::BegintoSwithAnim()
{
	InteractState = EInteractState::Empty;
	SwitchLinkLayerAnim();//动画通知后，此时可以进行切换，
}

void ADWCharacter::EndtoSwithBegin()
{
	InteractState = EInteractState::Empty;
	PlayBeginCharInteractAnim();
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


void ADWCharacter::BegintoInteract()
{
	//该函数绑定到按键回调，在这里面进行交互逻辑
	if (IsSocketOccpied())//插槽被占着就需要判断，没被占着就直接拿
	{
		//如果此时手中有，且视线没在可交互物体上，那么按e就是执行物体本身的操作
		if (CurrentFocusActor == nullptr)
		{
			IInteractableInterface::Execute_ItemOwnAction(CurrentItem);
			CurrentItem = nullptr;
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
					//这里播放end中的存入动画
					// PlayEndCharInteractAnim();
					CurrentItem->Destroy();
				}
				else//当包满后，无法存入，就需要将手中的东西给扔掉，然后在拾取地上的新东西	
				{
					//这里可以播放丢弃动画，当然我认为这里根本不需要为丢弃准备一个动画，直接脱离就行了
					// PlayEndCharInteractAnim();
					CurrentItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
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
					//丢弃动画也可以在这里播放,这里和上面一样，不需要特别的丢弃动画，就直接脱离就行了
					IInteractableInterface::Execute_SetItemPhysic(CurrentItem,true);
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
	FGameplayTag ItemTag = IInteractableInterface::Execute_GetTagFromItem(CurrentFocusActor);
	//这里播放角色的新交互，应该始终是先end再begin的思路。end是手中的物体，begin是对着的物体
	//1.空手，那么end动画是空，然后播放begin
	//2.手中有东西，此时应该是先播放手中东西的end动画，再播放新对象的begin动画，手中有分为两种，可存储和不可存储，可存储就单纯的一个收纳动作，不可存储直接不需要动画，空就行了
	//end动画只有空手空动画，收纳动画和放下动画
	//begin动画只有通用伸手动画，特殊物体的拾取动画
	PlayEndCharInteractAnim();//放这里是保证end一定会在交互中触发，这样才能触发后面的begin和animlayer。
	//end动画已经在上面处理了，现在在后面就播放这个自己的交互动画,不过这里需要注意的是不要让两个动画争抢
	// PlayBeginCharInteractAnim(ItemTag);//这里有角色自己播放自己对应的交互动画。
	IInteractableInterface::Execute_OnInterAct(CurrentFocusActor,this,this);
	CurrentItem = nullptr;//重置
	// SwitchLinkLayerAnim();//只需要有了交互操作，那么这个时候就直接切换动画，在蓝图中控制玩家重复按交互键导致的动画无效切换的漏洞
	//这里已知不会触发的边界情况：当玩家手里有东西，视线不对向可交互物体，此时按e会在上面第一种情况被处理。当玩家什么都没有但是按e会被上面处理，交互都不会执行
	//这里需要注意的情况，当交互的物体是不能拿在手中的，此时会将手中的东西丢弃或者收纳，那么就需要进行动画需要切换会原来的空手动画。
}

void ADWCharacter::PlayBeginCharInteractAnim()
{//内部判断是播放动画还是切换动画接口
	if(InteractState != EInteractState::Empty)return;
	InteractState = EInteractState::Equipping;
	if (CurrentFocusActor && CurrentFocusActor->Implements<UInteractableInterface>())
	{
		FGameplayTag TypeTag = IInteractableInterface::Execute_GetTagFromItem(CurrentFocusActor);
		FCharInteractAnim AnimAsset = PlayerInterActAnimAsset->GetRelevantAnimAssetbyTag(TypeTag);
		if (AnimAsset.BeginInteractAnim && FirstPersonMeshAnimIns)
		{
			FirstPersonMeshAnimIns->Montage_Play(AnimAsset.BeginInteractAnim,1.f);
		}
	}
	else
	{
		//视线没有对上东西，或者对上的东西不是可以交互的，那么这个时候直接调用动画接口切换函数
		SwitchLinkLayerAnim();//通知触发的函数里面需要重置state，所以这里我直接调用的是切换函数，便于我在这里切换状态
		InteractState = EInteractState::Empty;
	}
	
}

void ADWCharacter::PlayEndCharInteractAnim()
{
	if(InteractState != EInteractState::Empty)return;//动画的播放必须要保证在当前是empty的情况下在进行

	InteractState = EInteractState::Unequiping;
	if (!PlayerInterActAnimAsset)return;
	if (!CurrentItem)//手中是空的,直接设置状态为empty
	{
		InteractState = EInteractState::Empty;
		//调用后面的begin
		PlayBeginCharInteractAnim();
		return;
	}
	//手中有东西的情况,播放动画，然后会等动画通知触发endtoswitchbegin
	FGameplayTag TypeTag = IInteractableInterface::Execute_GetTagFromItem(CurrentItem);
	const FCharInteractAnim AnimAsset = PlayerInterActAnimAsset->GetRelevantAnimAssetbyTag(TypeTag);
	if (AnimAsset.EndInteractAnim && FirstPersonMeshAnimIns)
	{
		FirstPersonMeshAnimIns->Montage_Play(AnimAsset.EndInteractAnim,1.f);
	}
	else//处理边界情况，如果这个currentitem没有end动画，虽然这个情况基本在后期不会发生
	{
		InteractState = EInteractState::Empty;
		//调用后面的begin
		PlayBeginCharInteractAnim();
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

