// Tian Handong


#include "UI/DWHUD.h"

void ADWHUD::BeginPlay()
{
	Super::BeginPlay();
	if (OverlayWidgetClass)
	{
		OverlayWidget = CreateWidget<UDWUserWidget>(GetWorld(), OverlayWidgetClass);
		OverlayWidget->AddToViewport();
	}
}
