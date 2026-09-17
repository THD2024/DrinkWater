// Tian Handong


#include "Player/DWCharacter.h"
#include "Player/DWPlayerState.h"


ADWCharacter::ADWCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("FirstPersonMesh"));
	FirstPersonMesh->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(FirstPersonMesh);
	CameraComponent->SetRelativeLocation(FVector(8.f,0.f,0.f));
	CameraComponent->bUsePawnControlRotation = false;//交给弹簧臂
	
}


void ADWCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitInfo();//单机情况下，只需要在beginplay中进行actorinfo。
}


UAbilitySystemComponent* ADWCharacter::GetAbilitySystemComponent() const
{
	if (DwAbilitySystemComponent)
	{
		return DwAbilitySystemComponent;
	}
	return nullptr;
}

void ADWCharacter::InitInfo()
{
	//获取到playerstate中的asc复制到当前character的asc。
	if (ADWPlayerState* DWPlayerState = GetPlayerState<ADWPlayerState>())
	{
		DwAbilitySystemComponent = DWPlayerState->GetDWAbilitySystemComponent();
		DwAbilitySystemComponent->InitAbilityActorInfo(DWPlayerState,this);
	}
}

void ADWCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADWCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

