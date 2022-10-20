

#include "Components/InteractableComponent.h"

UInteractableComponent::UInteractableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UInteractableComponent::Interact(AActor* Initiator)
{
	OnInteract.Broadcast(Initiator);
}

void UInteractableComponent::BeginPlay()
{
	Super::BeginPlay();
}

