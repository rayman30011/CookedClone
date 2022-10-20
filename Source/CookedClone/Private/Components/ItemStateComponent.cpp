// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/ItemStateComponent.h"

// Sets default values for this component's properties
UItemStateComponent::UItemStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UItemStateComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UItemStateComponent::Step()
{
}

