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
	//这里面需要保证对应物体的逻辑和动画的对应
	//如果是拾取动画就要就要拾取，如果是交互动画，不要管,而且也只有拾取动画的情况需要切换动画蓝图
	//这里最妙的是，我的交互接口里面包含了对于拾取和普通交互的情况，我不需要在这里细分，我直接调用交互接口就行了
	if (!CurrentFocusActor || !CurrentFocusActor->Implements<UInteractableInterface>())
	{//保险吧，虽然这种情况也不可能发生
		InteractState = EInteractState::Empty;
		SwitchLinkLayerAnim();
	}
	IInteractableInterface::Execute_OnInterAct(CurrentFocusActor,this,this);
}

void ADWCharacter::EndtoSwithBegin()
{
	//进入这里表示动画时机到了，我们需要判断手中的东西是可收纳还是不可收纳，然后根据情况去写逻辑
	if (AActor*CurrentAttachActor =  GetCurrentAttachActor())//手中没东西的情况在playend中，处理了，这里还是留个心眼
	{
		if (CurrentAttachActor->ActorHasTag(FName("PNC")))//不可收纳
		{
			//直接脱落
			CurrentAttachActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		}
		else if (CurrentAttachActor->ActorHasTag(FName("PAC")))//可以收纳
		{
			if (CurrentAttachActor->Implements<UInteractableInterface>())
			{
				FGameplayTag IdentityTag = IInteractableInterface::Execute_GetTagFromItem(CurrentAttachActor);
				if (!UDWBlueprintFunctionLibrary::GetItemDataAssetFromGameState(this))return;
				FDWItemInfo Iteminfo = UDWBlueprintFunctionLibrary::GetItemDataAssetFromGameState(this)->GetItemInfoByTag(IdentityTag);
				if (!Iteminfo.Name.IsValid() || !Iteminfo.ItemPhoto)return;//如果名字是空,图片是空，那就说明返回的是个空的info，就不存，反之存.虽然这种情况逻辑上不存在，但是以防万一
				FItemBag BagInfo(Iteminfo.Name,Iteminfo.ItemPhoto);
				if (!AddItem(BagInfo))//添加,如果没添加成功就执行下面的逻辑，直接扔掉
				{
					CurrentAttachActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				}
			}
		}
	}
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
			// CurrentItem = AttachActor;//更新
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
	/*现在重新想，这个函数是当玩家按e后用来进行交互的第一层入口，这里面前置处理的是各种情况下比如手中有东西没有东西，我应该收纳还是直接
	 * 丢弃，但是现在动画进来了，出现问题了，不应该逻辑先行，而是动画先行，保证动画和逻辑衔接。这也就说明一件事，顺序反了。更合理的方法
	 * 应该是我不急于判断当前手中逻辑怎么走，而是先走对应的动画入口，然后被通知调用进入逻辑入口
	 * 当前情况应该重构为：
	 * 第一阶段：
	 * 进入该函数后，只有两种情况，一种当前的e是玩家随便乱按的，或者物体不可交互，这个时候直接退出函数，第二种情况，当前确实准心对准了可交互物体
	 * playendanim逻辑，在这个函数里面去处理是播放丢弃动画，收纳动画，还是不播动画，直接进入beginanim.
	 * 先不说进入到beginanim，当播放丢弃动画或者收纳动画后，应该在动画合适时机有一个通知，这个时候进逻辑，物品丢弃或者存入背包。
	 * 第二阶段：
	 * 进入到beginanim，在这里面处理交互的可拾取物体，还是单纯的交互物体，根据分类进入对应的逻辑分支，播放对应的动画，前者可拾取物体
	 * 有对应的拾取动画，这里需要动画通知来实现在某个合适的时间节点来拾取到。后者则只需要播放一个简单的交互动作，在动作末尾，有物体自己播放对应的交互动画
	 * 由于在第一阶段不可交互的情况被过滤了，所以不用考虑别的情况。当是简单的交互动作，也需要在动作末尾触发第三阶段。也就是说第三阶段入口是一致的，不会有多个
	 * 入口，具体情况在第三阶段函数内部进行分开
	 * 第三阶段:
	 * 这一阶段有两种情况，状态重置和切换蓝图动画重置，状态重置就是只需要设置为empty允许玩家下次e键交互
	 * 主要是第二种情况替换对应的动画蓝图，这里触发的情况只有一种情况，那么就是只有当是可拾取物体，拾取到了手上才需要进行动画蓝图切换，其他情况
	 * 都是单纯的播放一个伸手动画然后继续回到原来的动画蓝图。第三阶段触发情况只有拾取动画播放的末尾和物体到达手中的时机一致。
	 */
	if (!CurrentFocusActor || !Cast<UInteractableInterface>(CurrentFocusActor))
	{
		if (GetCurrentAttachActor() && GetCurrentAttachActor()->Implements<UInteractableInterface>())
		{
			IInteractableInterface::Execute_ItemOwnAction(GetCurrentAttachActor());
		}
	}
	//如果当前手中有东西，并且但是视线对上的是不可交互或者没有东西，这个时候应该考虑是对物体本身的操作而不是交互.
	if (InteractState != EInteractState::Empty)return;//防止当前在进行其他交互动作的时候，新的状态进来导致争抢
	PlayEndCharInteractAnim();//直接进入end逻辑，需要注意的是end逻辑这里，针对的是手中有的，而不是视线对着的
	
}

void ADWCharacter::PlayBeginCharInteractAnim()
{//内部判断是播放动画还是切换动画接口
	//两种情况：实现所对可在手上或不可在手上,前面过滤了视线所对物体为空或者不是可交互物体，这里不用额外判断
	//其实这里逻辑可以在简单一点，因为处理的两种情况都是要播放动画，这里只需要单纯播放动画，不需要判断额外，至于是拿到手上还是只一个动作就只需要在
	//通知调用的函数中处理了
	if(InteractState != EInteractState::Empty)return;
	InteractState = EInteractState::Equipping;
	if (CurrentFocusActor && CurrentFocusActor->Implements<UInteractableInterface>())
	{
		FGameplayTag TypeTag = IInteractableInterface::Execute_GetTagFromItem(CurrentFocusActor);
		FCharInteractAnim AnimAsset = PlayerInterActAnimAsset->GetRelevantAnimAssetbyTag(TypeTag);
		if (AnimAsset.BeginInteractAnim && FirstPersonMeshAnimIns)
		{
			FirstPersonMeshAnimIns->Montage_Play(AnimAsset.BeginInteractAnim,1.f);
			//montage动画播放后，会自己触发下一阶段，然后将状态重置为empty
		}
		else
		{
			//这里还有种情况，如果当前物体没有角色交互动画，或者还没有安装，那么应该直接设置状态为空，
			//这种情况后期基本上也不会存在，不过保险
			UE_LOG(LogTemp, Warning, TEXT("PlayBeginCharInteractAnim Anim Not Found"));
			InteractState = EInteractState::Empty;
		}
	}
	
}

void ADWCharacter::PlayEndCharInteractAnim()
{
	if(InteractState != EInteractState::Empty)return;//动画的播放必须要保证在当前是empty的情况下在进行

	InteractState = EInteractState::Unequiping;
	if (!PlayerInterActAnimAsset)//当数据资产没有设置
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerInterActAnimAsset is null"));
		InteractState = EInteractState::Empty;//状态要重置
		return;
	}
	if (!GetCurrentAttachActor())//手中是空的,直接设置状态为empty,不需要播放结束动画
	{//这里有一个边界情况，因为在上面我已经把currentitem存入后就将它销毁了，那么正常情况来看，这里的attachactor也是空的
		//但是事实上这并不是标准意义上的手中没有东西，而是我需要先收纳，手中才没有东西，也就是这种情况，我要先播放收纳动画，在销毁
		InteractState = EInteractState::Empty;
		//调用后面的begin
		PlayBeginCharInteractAnim();
		return;
	}
	//手中有东西的情况,播放动画，然后会等动画通知触发endtoswitchbegin
	FGameplayTag TypeTag = IInteractableInterface::Execute_GetTagFromItem(GetCurrentAttachActor());
	const FCharInteractAnim AnimAsset = PlayerInterActAnimAsset->GetRelevantAnimAssetbyTag(TypeTag);
	if (AnimAsset.EndInteractAnim && FirstPersonMeshAnimIns)
	{
		FirstPersonMeshAnimIns->Montage_Play(AnimAsset.EndInteractAnim,1.f);
		//播放对应的动画，丢弃或者收纳，在通知触发的函数中需要设置物体掉落或者消失根据不同的情况
	}
	else//处理边界情况，如果这个currentitem没有end动画，虽然这个情况基本在后期不会发生
	{
		InteractState = EInteractState::Empty;
		//调用后面的begin
		PlayBeginCharInteractAnim();
	}
}

void ADWCharacter::HandleAnimSwitch()
{
	//这被触发的思路也是清晰的，只有当这个物体可以被交互并且有动画的时候直接到这里来，就会被动画通知调用，动画切换逻辑就交给蓝图中的逻辑
	//这里需要明确，这个函数触发的入口就是Playanim后，通知触发的，但是该函数与BegintoSwithAnim是同步的，不是和以前一样begintoswithanim触发这个函数
	//这里面处理两种情况，状态重置和动画蓝图切换在状态重置
	//这里比较妙的是，我把当前切换的逻辑全部都放到了蓝图中所以我只需要下面两行代码就处理两种情况
	
	SwitchLinkLayerAnim();
	InteractState = EInteractState::Empty;
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

