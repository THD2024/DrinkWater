// Tian Handong


#include "UI/DWHUD.h"

void ADWHUD::InitOverlay(APlayerController* PC, APlayerState* PS)
{
	UDWUserWidget* Widget = CreateWidget<UDWUserWidget>(GetWorld(), OverlayWidgetClass);
	const FDWWidgeControllerParams Params(PC,PS);
	
	if (GetOverlayWidgetController(Params))
	{
		Widget->SetWidgetController(GetOverlayWidgetController(Params));
		Widget->AddToViewport();
	}
}

void ADWHUD::BeginPlay()
{
	Super::BeginPlay();
}

UOverlayWidgetController* ADWHUD::GetOverlayWidgetController(const FDWWidgeControllerParams& params)
{
	if (OverlayWidgetController == nullptr)
	{
		if (OverlayWidgetControllerClass)
		{
			OverlayWidgetController = NewObject<UOverlayWidgetController>(this,OverlayWidgetControllerClass);
			OverlayWidgetController->SetWidgetControllerParams(params);
			return OverlayWidgetController;
		}
	}
	return OverlayWidgetController;
}

UCueWidgeController* ADWHUD::GetCueWidgeController(const FDWWidgeControllerParams& params)
{
	if (CueWidgeController == nullptr)
	{
		if (CueWidgetControllerClass)
		{
			CueWidgeController = NewObject<UCueWidgeController>(this,CueWidgetControllerClass);
			CueWidgeController->SetWidgetControllerParams(params);
			return CueWidgeController;
		}
	}
	return CueWidgeController;
}
