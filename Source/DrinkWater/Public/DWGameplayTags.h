// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include"GameplayTagContainer.h"

/**
 * 
 */

struct FDwGameplayTags
{
public:
	static const FDwGameplayTags& Get(){return GameplayTags;}
	
	static void InitializeGameplayTags();
	
	FGameplayTag Item_Type_Canbinet;
	FGameplayTag Item_Type_Banana;
	FGameplayTag Item_Type_Flashlight;
	
	private:
	static FDwGameplayTags GameplayTags;
};