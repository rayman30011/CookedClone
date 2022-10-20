// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleTable.generated.h"

UCLASS()
class COOKEDCLONE_API ASimpleTable : public AActor
{
	GENERATED_BODY()
	
public:
	ASimpleTable();

	UFUNCTION()
	void TakeItem(class ASimpleItem* Item);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInteractableComponent* InteractableComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* ItemPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnInteract(AActor* Initiator);

private:
	class ASimpleItem* CurrentItem;

public:
};
