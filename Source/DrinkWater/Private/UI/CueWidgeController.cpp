// Tian Handong


#include "UI/CueWidgeController.h"

#include "Player/DWCharacter.h"

void UCueWidgeController::BindCallBack()
{
	Super::BindCallBack();
	if (PC && PC->GetPawn())
	{
		if (ADWCharacter* Player = Cast<ADWCharacter>(PC->GetPawn()))
		{
			Player->OnTriggerCueWidget.AddUObject(this, &UCueWidgeController::TriggerCueWidget);
		}
	}
}

void UCueWidgeController::BroadInitValue()
{
	Super::BroadInitValue();

}

void UCueWidgeController::TriggerCueWidget(bool CanTrigger)
{
	TriggerDelegate.Broadcast(CanTrigger);
}
