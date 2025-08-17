// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionDataTypes.h"
#include "Interactable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteraction);

UCLASS(ClassGroup=(Custom), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class INTERACTIONRUNTIME_API UInteractable : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractable();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void AddInteractor(const UObject* NewInteractor);
	UFUNCTION()
	void RemoveInteractor(const UObject* OldInteractor);
	UFUNCTION()
	void OnInteractionRequest();

	UFUNCTION(Server, Reliable)
	void Interaction();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	EInteractionType InteractionType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	EInteractionState InteractionState;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteraction OnInteraction;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess))
	TArray<const UObject*> Interactors;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess))
	int32 InteractableCount;
};
