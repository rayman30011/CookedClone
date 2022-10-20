// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CrateComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COOKEDCLONE_API UCrateComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCrateComponent();

protected:
	UPROPERTY(EditAnywhere)
	FDataTableRowHandle ItemsRowHandle;

	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void Interact(class ACookedCharacter* Character);

private:
	struct FItemRow* ItemRow;
};
