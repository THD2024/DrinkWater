// Tian Handong


#include "Notify/InterActAnimNotify.h"
#include"Player/DWCharacter.h"

void UInterActAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp || !MeshComp->GetOwner())return;
	if (ADWCharacter* Char = Cast<ADWCharacter>(MeshComp->GetOwner()))
	{
		Char->TimetoSwithAnim();
	}
}
