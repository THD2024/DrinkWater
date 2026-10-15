// Tian Handong


#include "BlueprintFunctionLibrary/DWBlueprintFunctionLibrary.h"
#include "GameFramework/PlayerState.h"
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
