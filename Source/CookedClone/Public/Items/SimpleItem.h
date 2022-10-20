// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "SimpleItem.generated.h"

UCLASS()
class COOKEDCLONE_API ASimpleItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleItem();

	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UInteractableComponent* InteractableComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* Mesh;


	virtual void BeginPlay() override;


	UFUNCTION()
	virtual void OnInteract(AActor* Initiator);

public:

};


UENUM(BlueprintType)
enum class EItemOperationType : uint8
{
	Cut = 0		UMETA(DisplayName = "Cut"),
	Fry = 1		UMETA(DisplayName = "Fry"),
	Cook = 2	UMETA(DisplayName = "Cook"),
};

USTRUCT(BlueprintType)
struct FItemRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ASimpleItem> ItemClass;
};


USTRUCT(BlueprintType)
struct FItemsMapRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName From;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EItemOperationType Operation;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName To;
};
