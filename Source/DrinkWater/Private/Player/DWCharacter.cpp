// Tian Handong


#include "Player/DWCharacter.h"

#include "Chaos/SoftsSpring.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/DWPlayerState.h"


ADWCharacter::ADWCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetMesh(), BoneName);//将弹簧臂挂到头上
	SpringArmComponent->TargetArmLength = 0.f;
	SpringArmComponent->bUsePawnControlRotation = true;//跟随玩家旋转
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent,USpringArmComponent::SocketName);
	CameraComponent->SetRelativeLocation(FVector(8.f,0.f,0.f));
	CameraComponent->bUsePawnControlRotation = false;//交给弹簧臂
	
}


void ADWCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitInfo();//单机情况下，只需要在beginplay中进行actorinfo。
	GetMesh()->HideBoneByName(BoneName, EPhysBodyOp::PBO_Term);
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

