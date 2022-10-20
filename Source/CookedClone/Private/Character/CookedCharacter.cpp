// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CookedCharacter.h"
#include "Items/SimpleItem.h"
#include "Components/SceneComponent.h"
#include "Components/InteractableComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Items/SimpleItem.h"

DEFINE_LOG_CATEGORY_STATIC(LogCookedCharacter, All, All);

ACookedCharacter::ACookedCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	InteractPoint = CreateDefaultSubobject<USceneComponent>("InteractPoint");
	InteractPoint->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	ItemPoint = CreateDefaultSubobject<USceneComponent>("ItemPoint");
	ItemPoint->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ACookedCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ACookedCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		AddMovementInput(FVector::ForwardVector, Value);
	}
}

void ACookedCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		AddMovementInput(FVector::RightVector, Value);
	}
}

void ACookedCharacter::Interact()
{
	UE_LOG(LogCookedCharacter, Display, TEXT("Player try interact"));

	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Visibility));
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	UClass* SeekClass = AActor::StaticClass();

	const auto Position = InteractPoint->GetComponentTransform().GetLocation();

	TArray<AActor*> OutActors;
	TArray<AActor*> IgnoreActors = { GetOwner(), this };
	if (CurrentItem) IgnoreActors.Add(CurrentItem);

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), Position, InteractRadius, TraceObjectTypes, SeekClass, IgnoreActors, OutActors);
	DrawDebugSphere(GetWorld(), Position, InteractRadius, 8, FColor::Green, false, 2.f);

	UE_LOG(LogCookedCharacter, Display, TEXT("Founded %d items"), OutActors.Num());
	if (OutActors.Num() != 0)
	{
		auto It = OutActors.begin();
		AActor* NearestActor = *It;
		float NearestActorDistance = FVector::Distance(NearestActor->GetActorLocation(), Position);

		++It;

		for (; It != OutActors.end(); ++It)
		{
			float Distance = FVector::Distance((*It)->GetActorLocation(), Position);
			if (Distance < NearestActorDistance)
			{
				NearestActor = *It;
				NearestActorDistance = Distance;
			}
		}

		if (NearestActor)
		{
			auto* InteractableComponent = NearestActor->FindComponentByClass<UInteractableComponent>();
			if (InteractableComponent)
			{
				InteractableComponent->Interact(this);
			}
		}
	}
	else 
	{
		TryUntakeCurrentItem();
	}
}

void ACookedCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ACookedCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ACookedCharacter::MoveRight);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ACookedCharacter::Interact);
}

bool ACookedCharacter::TryTakeItem(ASimpleItem* Item)
{
	if (!Item) return false;

	UE_LOG(LogCookedCharacter, Display, TEXT("Try take [%s]"), *Item->GetName());
	
	TryUntakeCurrentItem();
	
	Item->GetMesh()->SetSimulatePhysics(false);
	Item->SetActorEnableCollision(false);
	Item->AttachToComponent(ItemPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	CurrentItem = Item;

	return true;
}

bool ACookedCharacter::TryUntakeCurrentItem()
{
	UE_LOG(LogCookedCharacter, Display, TEXT("Try untake"));

	if (!CurrentItem) return false;

	CurrentItem->GetMesh()->SetSimulatePhysics(true);
	CurrentItem->SetActorEnableCollision(true);
	CurrentItem->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);

	CurrentItem = nullptr;
	return true;
}

