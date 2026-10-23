// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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
	
	FGameplayTag& GetIdentityTag(){return IdentityTag;}
	
	void SetPhysicalSimulation(bool CanPhysicalSimulate);

protected:
	virtual void BeginPlay() override;
	
	virtual void OnInterAct_Implementation(const AActor* OverlapActor) override;
	
	virtual void OnFocus_Implementation() override;
	
	virtual void OnUnFocus_Implementation() override;
	
	virtual void ItemOwnAction_Implementation() override;
	
	virtual FGameplayTag GetTagFromItem_Implementation() override;
	
	
	UFUNCTION(BlueprintImplementableEvent)
	void OwnInteractAnim();//表示该item自身的动画，比如柜子开门
	
	UFUNCTION(BlueprintImplementableEvent)
	void StartItemOwnAction();
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> ItemMesh;//通用
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> SphereCollision;//通用
	
	UPROPERTY(EditAnywhere)
	FName SocketName = FName("");
	
	UPROPERTY(EditAnywhere)
	FGameplayTag IdentityTag;//用来在dataasset中获取到对应的类的基本信息
	
public:	
	virtual void Tick(float DeltaTime) override;

};




