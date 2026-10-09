// Tian Handong


#include "Player/DWCharacter.h"

#include <string>

#include "Player/DWPlayerState.h"


ADWCharacter::ADWCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	
	
}

void ADWCharacter::ExecutePhysicalJump()
{
	Jump();
}


void ADWCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitInfo();//单机情况下，只需要在beginplay中进行actorinfo。
	OnTurnDetermined.AddUObject(this,&ADWCharacter::PlayTurnAnimation);
}


UAbilitySystemComponent* ADWCharacter::GetAbilitySystemComponent() const
{
	if (DwAbilitySystemComponent)
	{
		return DwAbilitySystemComponent;
	}
	return nullptr;
}

void ADWCharacter::FaceRotation(FRotator NewControlRotation, float DeltaTime)
{
	const float CurrentYaw = GetActorRotation().Yaw;
	const float ControlYaw = NewControlRotation.Yaw;
	if (IsInPlacing)
	{
		TurnAngle = FMath::FindDeltaAngleDegrees(CurrentYaw,ControlYaw);
		if (!bIsTurning && FMath::Abs(TurnAngle) >= 45)
		{
			bIsTurning = true;
			DetermineTurnType();
		}
	
		if ( bIsTurning)
		{
			if (FMath::Abs(TurnAngle) < 1.f)
			{
				bIsTurning = false;
				return;
			}
			//原地转身
			const float TurnSpeed = 180.f;
			const float DeltaYaw = FMath::Clamp(
			TurnAngle,
			-TurnSpeed*DeltaTime,
			TurnSpeed*DeltaTime
			);
			AddActorWorldRotation(
				FRotator(0.f,DeltaYaw,0.f)
			);
			return;
		}
		
	}
	bIsTurning = false;
	TurnAngle = 0.f;
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

void ADWCharacter::DetermineTurnType()
{
	//在这里判断需要播放的转身动画类型
	if (!bIsTurning || !IsInPlacing)return;//保证在条件合适的情况在才能去选择转身动画类型
	
	if (FMath::Abs(TurnAngle) >= 135.f)
	{
		if (TurnAngle > 0)
		{
			TurnType = ETurnType::Turn180Right;
		}
		else
		{
			TurnType = ETurnType::Turn180Left;
		}
	}
	else
	{
		if (TurnAngle > 0)
		{
			TurnType = ETurnType::Turn90Right;
		}
		else
		{
			TurnType = ETurnType::Turn90Left;
		}
	}
	OnTurnDetermined.Broadcast(TurnType);
}

void ADWCharacter::PlayTurnAnimation(ETurnType InTurnType)
{
	switch (InTurnType)
	{
	case ETurnType::Turn90Left:
		// 90° Left Montage
		if (Left90Montage)PlayAnimMontage(Left90Montage);
		CurrentMontage = Left90Montage;
		break;

	case ETurnType::Turn90Right:
		// 90° Right 
		if (Right90Montage)PlayAnimMontage(Right90Montage);
		CurrentMontage = Right90Montage;
		break;

	case ETurnType::Turn180Left:
		// 180° Left Montage
		if (Left180Montage)PlayAnimMontage(Left180Montage);
		CurrentMontage = Left180Montage;
		break;

	case ETurnType::Turn180Right:
		// 180° Right Montage
		if (Right180Montage)PlayAnimMontage(Right180Montage);
		CurrentMontage = Right180Montage;
		break;
	
	default:
		CurrentMontage = nullptr;
		break;
	}
}

bool ADWCharacter::SampleBoneComponentSpaceYaw(const UAnimSequence* Sequence, float SequenceTime, FName BoneName,
	float& OutYaw)
{
	OutYaw = 0.f;

	if (!Sequence || !Sequence->GetSkeleton())
	{
		return false;
	}

	USkeleton* Skeleton = Sequence->GetSkeleton();

	// 1. 查找目标骨骼在 Skeleton 中的索引
	const int32 BoneIndex =
		Skeleton->GetReferenceSkeleton().FindBoneIndex(BoneName);

	if (BoneIndex == INDEX_NONE)
	{
		return false;
	}

	// 2. 准备目标骨骼及其全部父骨骼
	// FCompactPose 使用的临时内存需要在本函数结束时释放
	FMemMark Mark(FMemStack::Get());

	TArray<FBoneIndexType> RequiredBones;
	RequiredBones.Add(BoneIndex);

	Skeleton->GetReferenceSkeleton()
		.EnsureParentsExistAndSort(RequiredBones);

	UE::Anim::FCurveFilterSettings FilterSettings;

	const FBoneContainer BoneContainer(
		RequiredBones,
		FilterSettings,
		*Skeleton
	);

	const FCompactPoseBoneIndex CompactBoneIndex =
		BoneContainer.MakeCompactPoseIndex(
			FMeshPoseBoneIndex(BoneIndex)
		);

	// 3. 按指定时间采样动画姿势
	FCompactPose Pose;
	Pose.SetBoneContainer(&BoneContainer);

	FBlendedCurve Curve;
	Curve.InitFrom(BoneContainer);

	const FAnimExtractContext Context(
		static_cast<double>(SequenceTime),
		false
	);

	UE::Anim::FStackAttributeContainer Attributes;

	FAnimationPoseData PoseData(
		Pose,
		Curve,
		Attributes
	);

	// false：不强制读取原始动画数据
	Sequence->GetBonePose(
		PoseData,
		Context,
		true
	);

	if (!Pose.IsValidIndex(CompactBoneIndex))
	{
		return false;
	}

	// 4. 将局部骨骼姿势转换为 Component Space
	FCSPose<FCompactPose> ComponentPose;
	ComponentPose.InitPose(Pose);

	const FTransform BoneTransform =
		ComponentPose.GetComponentSpaceTransform(
			CompactBoneIndex
		);

	// 5. 仅返回目标骨骼的 Component Space Yaw
	OutYaw = BoneTransform.GetRotation().Rotator().Yaw;

	return true;
}

bool ADWCharacter::GetCurrentTurnRootAnimYaw(float& OutYaw,FName BoneName)
{
	OutYaw = 0.f;
	if (!CurrentMontage)return false;
	
	UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr;
	
	if (!AnimInstance || !AnimInstance->Montage_IsActive(CurrentMontage))return false;
	
	//获取当前montage播放时间
	const float MontageTime = AnimInstance->Montage_GetPosition(CurrentMontage);
	//获取当前对应的动画片段
	for (const FSlotAnimationTrack& SlotTrack : CurrentMontage->SlotAnimTracks)
	{
		const FAnimSegment* Segment = SlotTrack.AnimTrack.GetSegmentAtTime(MontageTime);
		if (!Segment) continue;
		
		float SequenceTime = 0.f;
		UAnimSequenceBase* AnimSequenceBase = Segment->GetAnimationData(MontageTime,SequenceTime);
		const UAnimSequence* Sequence = Cast<UAnimSequence>(AnimSequenceBase);
		if (!Sequence || !Sequence->GetSkeleton())continue;
		
		// const int32 RootBondIndex = Sequence->GetSkeleton()->GetReferenceSkeleton().FindBoneIndex(FName(""));
		
		// if (RootBondIndex == INDEX_NONE)continue;
		
		FTransform RootTransform = FTransform::Identity;
		// Sequence->GetBoneTransform(RootTransform,FSkeletonPoseBoneIndex(RootBondIndex),SequenceTime,false);
		// OutYaw = RootTransform.Rotator().Yaw;
		GEngine->AddOnScreenDebugMessage(1,1.f,FColor::Black,FString::Printf(TEXT("MontageTime:: %.2f"),MontageTime));

		return SampleBoneComponentSpaceYaw(
			Sequence,
			SequenceTime,
			BoneName,
			OutYaw
			);
		
	}
	return false;
}


void ADWCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (IsJumpStarting == false && GetVelocity().Size2D() < 50)
	{
		IsInPlacing = true;
	}
	else
	{
		IsInPlacing = false;
	}
}

void ADWCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

