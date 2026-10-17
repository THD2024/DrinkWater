// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Interaction/InteractableInterface.h"
#include "DWItem.generated.h"

UCLASS()
class DRINKWATER_API ADWItem : public AActor , public IInteractableInterface
{//父类，仅可交互
	GENERATED_BODY()
	
public:	
	ADWItem();

protected:
	virtual void BeginPlay() override;
	
	virtual void OnInterAct_Implementation(const AActor* OverlapActor) override;
	
	virtual void OnFocus_Implementation() override;
	
	virtual void OnUnFocus_Implementation() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void CabintOpenandClose();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> ItemMesh;//通用
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> SphereCollision;//通用
	
	UPROPERTY(EditAnywhere)
	FName SocketName = FName("");
	
public:	
	virtual void Tick(float DeltaTime) override;

};




