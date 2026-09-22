// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Player/DWCharacter.h"
#include "DWAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class DRINKWATER_API UDWAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};

inline void UDWAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
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


