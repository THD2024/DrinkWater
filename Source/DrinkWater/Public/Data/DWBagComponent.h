// Tian Handong

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DWBagComponent.generated.h"


USTRUCT(Blueprintable)
struct FItemBag
{
	GENERATED_BODY()
public:
	FItemBag() : ItemName(NAME_None) , ItemPhoto(nullptr){}
	FItemBag(FName Name, UTexture2D* Photo) : ItemName(Name), ItemPhoto(Photo){}
	
	UPROPERTY(BlueprintReadOnly)
	FName ItemName = FName("");
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTexture2D> ItemPhoto = nullptr;
	
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DRINKWATER_API UDWBagComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDWBagComponent();
	
	bool AddItemtoBag(const FItemBag& ItemBagInfo);
	

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TArray<FItemBag> Bag;
	
	UPROPERTY(EditAnywhere)
	float MaxVolumn = 6;//默认为6个插槽.

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
