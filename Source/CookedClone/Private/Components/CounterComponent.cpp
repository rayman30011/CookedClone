// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CounterComponent.h"
#include "Character/CookedCharacter.h"
#include "Items/SimpleItem.h"

DEFINE_LOG_CATEGORY_STATIC(LogCounterComponent, All, All);

UCounterComponent::UCounterComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCounterComponent::TakeItem(ASimpleItem* Item)
{
	if (AvailableItemsIds.Contains("All"))
	{
		UE_LOG(LogCounterComponent, Warning, TEXT("Avaibable All"));
	}
	
	Item->GetMesh()->SetSimulatePhysics(false);
	Item->SetActorEnableCollision(false);
	Item->AttachToComponent(PointComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	CurrentItem = Item;
}


void UCounterComponent::BeginPlay()
{
	Super::BeginPlay();

	auto PointComponents = GetOwner()->GetComponentsByTag(USceneComponent::StaticClass(), "Point");
	check(PointComponents.Num());
	PointComponent = Cast<USceneComponent>(PointComponents[0]);
}

void UCounterComponent::Interact(ACookedCharacter* Character)
{
	if (!Character)
		return;

	auto CharacterItem = Character->GetCurrentItem();

	if (CurrentItem && !CharacterItem)
	{
		if (!Character->TryTakeItem(CurrentItem))
		{
			UE_LOG(LogCounterComponent, Warning, TEXT("Cant take Item"));
		}
		else
		{
			CurrentItem = nullptr;
		}
	}
	else if (CurrentItem && CharacterItem)
	{
		// Обьединене
	}
	else if (!CurrentItem && CharacterItem)
	{
		Character->SetCurrentItem(nullptr);
		TakeItem(CharacterItem);
	}
}


