// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/SimpleItem.h"
#include "Components/InteractableComponent.h"
#include "Components/SceneComponent.h"
#include "Character/CookedCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogSimpleItem, All, All);


// Sets default values
ASimpleItem::ASimpleItem()
{
	PrimaryActorTick.bCanEverTick = false;

	InteractableComponent = CreateDefaultSubobject<UInteractableComponent>("InteractableComponent");
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ASimpleItem::BeginPlay()
{
	Super::BeginPlay();

	InteractableComponent->OnInteract.AddDynamic(this, &ASimpleItem::OnInteract);
}

void ASimpleItem::OnInteract(AActor* Initiator)
{
	UE_LOG(LogSimpleItem, Display, TEXT("Interact"));

	auto* Character = Cast<ACookedCharacter>(Initiator);
	if (Character)
		Character->TryTakeItem(this);
}

