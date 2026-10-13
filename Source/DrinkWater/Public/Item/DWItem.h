// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Interaction/InteractableInterface.h"
#include "DWItem.generated.h"

UCLASS()
class DRINKWATER_API ADWItem : public AActor , public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	ADWItem();

protected:
	virtual void BeginPlay() override;
	
	virtual void OnInterAct_Implementation(const AActor* OverlapActor) override;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USkeletalMeshComponent> ItemMesh;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> SphereCollision;
	
	UPROPERTY(EditAnywhere)
	FName SocketName = FName("");
	
public:	
	virtual void Tick(float DeltaTime) override;

};
