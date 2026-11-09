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
	FGameplayTag Item_Type_Door;
	
	private:
	static FDwGameplayTags GameplayTags;
};