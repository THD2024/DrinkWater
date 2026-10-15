// Tian Handong


#include "UI/DWUserWidget.h"

void UDWUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	OnWidgetControllerSet();
}
