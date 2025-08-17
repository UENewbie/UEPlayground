// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"

#include "Net/UnrealNetwork.h"


UInteractable::UInteractable()
{
	PrimaryComponentTick.bCanEverTick = true;
	UActorComponent::SetComponentTickEnabled(false);
	
	// Interaction DefaultSettings
	InteractionType = EInteractionType::None;
	InteractionState = EInteractionState::None;
	InteractableCount = 3;

	SetIsReplicatedByDefault(true);
}


void UInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

void UInteractable::AddInteractor(const UObject* NewInteractor)
{
	if (NewInteractor && !Interactors.Contains(NewInteractor))
	{
		Interactors.Add(NewInteractor);
	}
}

void UInteractable::RemoveInteractor(const UObject* OldInteractor)
{
	if (OldInteractor && Interactors.Contains(OldInteractor))
	{
		Interactors.Remove(OldInteractor);
	}
}

void UInteractable::OnInteractionRequest()
{
	if (InteractionState == EInteractionState::Interactable)
	{
		Interaction();
	}
}

void UInteractable::Interaction_Implementation()
{
	OnInteraction.Broadcast();

	InteractableCount--;
	GEngine->AddOnScreenDebugMessage(-1, 300.f, FColor::Red, TEXT("Interactable::Interaction Success! Remaining: ") + FString::FromInt(InteractableCount));
	if (InteractableCount <= 0)
	{
		InteractionState = EInteractionState::Completed;
	}
}
