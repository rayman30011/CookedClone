// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CrateComponent.h"
#include "Engine/DataTable.h"
#include "Items/SimpleItem.h"
#include "Character/CookedCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogCrateComponent, All, All)

UCrateComponent::UCrateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UCrateComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCrateComponent::Interact(ACookedCharacter* Character)
{
	if (!Character || Character->GetCurrentItem()) return;

	auto Row = ItemsRowHandle.GetRow<FItemRow>(TEXT("Context"));
	auto Item = Cast<ASimpleItem>(GetWorld()->SpawnActor(Row->ItemClass));
	if (!Character->TryTakeItem(Item))
	{
		UE_LOG(LogCrateComponent, Warning, TEXT("Cannot take item"))
	}
}

