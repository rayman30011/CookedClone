// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemStateComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCompleted);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COOKEDCLONE_API UItemStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UItemStateComponent();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float StepSize = 0.1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float CurrentStep = 0.f;

	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void Step();
};
