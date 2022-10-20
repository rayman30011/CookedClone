// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CounterComponent.generated.h"

class ASimpleItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COOKEDCLONE_API UCounterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCounterComponent();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ASimpleItem* GetCurrentItem() const { return CurrentItem; }

	UFUNCTION()
	void TakeItem(ASimpleItem* Item);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FName> AvailableItemsIds;

public:	
	UFUNCTION(BlueprintCallable)
	void Interact(class ACookedCharacter* Character);

private:
	USceneComponent* PointComponent;
	ASimpleItem* CurrentItem;
};
