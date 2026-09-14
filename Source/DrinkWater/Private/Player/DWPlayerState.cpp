// Tian Handong


#include "Player/DWPlayerState.h"

ADWPlayerState::ADWPlayerState()
{
	//单机，所以不需要设置复制
	DWAbilitySystemComponent = CreateDefaultSubobject<UDWAbilitySystemComponent>("UDWASC");
}

TObjectPtr<UDWAbilitySystemComponent> ADWPlayerState::GetDWAbilitySystemComponent() 
{
	if (DWAbilitySystemComponent)
	{
		return DWAbilitySystemComponent;
	}
	return nullptr;
}
