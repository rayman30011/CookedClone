// Fill out your copyright notice in the Description page of Project Settings.


#include "Tables/SimpleTable.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/InteractableComponent.h"
#include "Character/CookedCharacter.h"
#include "Items/SimpleItem.h"

DEFINE_LOG_CATEGORY_STATIC(LogSimpleTable, All, All)

ASimpleTable::ASimpleTable()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>("InteractableComponent");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	ItemPoint = CreateDefaultSubobject<USceneComponent>("ItemPoint");

	RootComponent = Mesh;
	ItemPoint->SetupAttachment(RootComponent);
}

void ASimpleTable::TakeItem(ASimpleItem* Item)
{
	Item->GetMesh()->SetSimulatePhysics(false);
	Item->SetActorEnableCollision(false);
	Item->AttachToComponent(ItemPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	CurrentItem = Item;
}

void ASimpleTable::BeginPlay()
{
	Super::BeginPlay();
	
	InteractableComponent->OnInteract.AddDynamic(this, &ASimpleTable::OnInteract);
}

void ASimpleTable::OnInteract(AActor* Initiator)
{
	auto Character = Cast<ACookedCharacter>(Initiator);
	if (!Character)
		return;

	auto CharacterItem = Character->GetCurrentItem();

	if (CurrentItem && !CharacterItem)
	{
		if (!Character->TryTakeItem(CurrentItem))
		{
			UE_LOG(LogSimpleTable, Warning, TEXT("Cant take Item"));
		}
		else
		{
			CurrentItem = nullptr;
		}
	}
	else if (CurrentItem && CharacterItem)
	{
		// Обьеденение
	}
	else if (!CurrentItem && CharacterItem)
	{
		Character->SetCurrentItem(nullptr);
		TakeItem(CharacterItem);
	}
}

