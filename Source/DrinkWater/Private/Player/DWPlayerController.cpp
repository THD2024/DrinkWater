// Tian Handong


#include "Player/DWPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"

ADWPlayerController::ADWPlayerController()
{
	
}

void ADWPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(DWContext,0);
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
		EnhancedInputComponent->BindAction(Move,ETriggerEvent::Triggered,this,&ADWPlayerController::HandleMove);
		EnhancedInputComponent->BindAction(Jump,ETriggerEvent::Triggered,this,&ADWPlayerController::HandleJump);
		EnhancedInputComponent->BindAction(Crouch,ETriggerEvent::Triggered,this,&ADWPlayerController::HandleCrouch);
	}
}

void ADWPlayerController::HandleMove(const FInputActionValue& Value)
{
	//处理前后左右的移动
	const FVector2D MoveVector = Value.Get<FVector2D>();
	
	FRotator ControllerRotation = GetControlRotation();
	FRotator YawRotation = FRotator(0.f,ControllerRotation.Yaw,0.f);
	
	APawn* ControllerPawn = GetPawn();
	if (!Player)return;
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	ControllerPawn->AddMovementInput(ForwardDirection,MoveVector.Y);
	ControllerPawn->AddMovementInput(RightDirection,MoveVector.X);
	
}

void ADWPlayerController::HandleJump(const FInputActionValue& Value)
{
	if (GetCharacter())
	{
		GetCharacter()->Jump();//内置跳跃
	}
}

void ADWPlayerController::HandleCrouch(const FInputActionValue& Value)
{
	if (GetCharacter())
	{
		GetCharacter()->Crouch();//内置蹲着
	}
}

void ADWPlayerController::HandleLook(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	AddYawInput(LookVector.X);
	AddPitchInput(LookVector.Y);
}
