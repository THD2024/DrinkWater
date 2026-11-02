// Tian Handong


#include "Notify/BeginAnimNotify.h"
#include"Player/DWCharacter.h"

void UBeginAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp || !MeshComp->GetOwner())return;
	if (ADWCharacter* Char = Cast<ADWCharacter>(MeshComp->GetOwner()))
	{
		//当动画播放后直接调用这两个函数用来分别处理第三阶段动画切换和物体逻辑
		Char->BegintoSwithAnim();
		Char->HandleAnimSwitch();
	}
}
