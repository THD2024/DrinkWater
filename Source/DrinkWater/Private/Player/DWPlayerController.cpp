// Tian Handong


#include "Player/DWPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


ADWPlayerController::ADWPlayerController()
{
	
}

void ADWPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bIsCouching = false;
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(DWContext,0);
	if (PlayerCameraManager)
	{
		PlayerCameraManager->ViewPitchMax = 35.f;
		PlayerCameraManager->ViewPitchMin = -80.f;
	}
}

void ADWPlayerController::AcknowledgePossession(class APawn* P)
{
	Super::AcknowledgePossession(P);
}

void ADWPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(Crouch,ETriggerEvent::Started,this,&ADWPlayerController::HandleCrouch);
		EnhancedInputComponent->BindAction(Run,ETriggerEvent::Triggered,this,&ADWPlayerController::HandleRun);
		EnhancedInputComponent->BindAction(Run,ETriggerEvent::Completed,this,&ADWPlayerController::HandleStopRun);
	}
}


void ADWPlayerController::HandleCrouch(const FInputActionValue& Value)
{
	if (GetCharacter())
	{
		if (bIsCouching)
		{
			GetCharacter()->UnCrouch();
		}
		else
		{
			GetCharacter()->Crouch();//内置蹲着
		}
	}
}

void ADWPlayerController::HandleRun(const FInputActionValue& Value)
{
	if (GetCharacter() && GetCharacter()->GetCharacterMovement())
	{
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
}

void ADWPlayerController::HandleStopRun(const FInputActionValue& Value)
{
	if (GetCharacter() && GetCharacter()->GetCharacterMovement())
	{
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}


