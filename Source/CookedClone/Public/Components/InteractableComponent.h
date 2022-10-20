// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractDelegate, AActor*, Initiator);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COOKEDCLONE_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractableComponent();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractDelegate OnInteract;


	void Interact(AActor* Initiator);

protected:
	virtual void BeginPlay() override;

public:	
};
