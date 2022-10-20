// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CookedCharacter.generated.h"

class ASimpleItem;

UCLASS()
class COOKEDCLONE_API ACookedCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACookedCharacter();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE ASimpleItem* GetCurrentItem() const { return CurrentItem; }

	FORCEINLINE void SetCurrentItem(ASimpleItem* Val) { CurrentItem = Val; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* InteractPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USceneComponent* ItemPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InteractRadius = 40.f;

	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void Interact();

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	bool TryTakeItem(ASimpleItem* Item);

	UFUNCTION(BlueprintCallable)
	bool TryUntakeCurrentItem();

private:
	ASimpleItem* CurrentItem;
};
