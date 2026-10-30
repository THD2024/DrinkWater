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
		Char->BegintoSwithAnim();
	}
}
