// Tian Handong


#include "Notify/AnimNotify_End.h"

#include "Player/DWCharacter.h"

void UAnimNotify_End::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                             const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (MeshComp && MeshComp->GetOwner())
	{
		if (ADWCharacter* Char = Cast<ADWCharacter>(MeshComp->GetOwner()))
		{
			Char->EndtoSwithBegin();
		}
	}
}
