// Tian Handong


#include "BlueprintFunctionLibrary/DWBlueprintFunctionLibrary.h"

#include "Core/DWGameStateBase.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "UI/DWHUD.h"

UCueWidgeController* UDWBlueprintFunctionLibrary::GetCueWidgetController(const UObject* WorldContextObject,
                                                                         APlayerController* PlayerController)
{
	if (PlayerController && PlayerController->GetPlayerState<APlayerState>())
	{
		APlayerState* PS = PlayerController->GetPlayerState<APlayerState>();
		if (ADWHUD* Hud = PlayerController->GetHUD<ADWHUD>())
		{
			FDWWidgeControllerParams Params(PlayerController,PS);
			return Hud->GetCueWidgeController(Params);
		}
	}
	return nullptr;
}

UDWItemDataAsset* UDWBlueprintFunctionLibrary::GetItemDataAssetFromGameState(const UObject* WorldContextObject)
{
	ADWGameStateBase* GameState = Cast<ADWGameStateBase>(UGameplayStatics::GetGameState(WorldContextObject));
	if (GameState)
	{
		return GameState->GetItemDataAsset();
	}
	
	return nullptr;
}

UAnimLayerDataAsset* UDWBlueprintFunctionLibrary::GetAnimLayerDataAssetFromGameState(const UObject* WorldContextObject)
{
	ADWGameStateBase* GameState = Cast<ADWGameStateBase>(UGameplayStatics::GetGameState(WorldContextObject));
	if (GameState)
	{
		return GameState->GetAnimLayerDataAsset();
	}
	return nullptr;
}
