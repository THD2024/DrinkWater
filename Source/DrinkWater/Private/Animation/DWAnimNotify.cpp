// Tian Handong


#include "Animation/DWAnimNotify.h"

 void UDWAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ADWCharacter* DWPlayer = Cast<ADWCharacter>(MeshComp->GetOwner()))
		{
			DWPlayer->ExecutePhysicalJump();
		}
	}
}