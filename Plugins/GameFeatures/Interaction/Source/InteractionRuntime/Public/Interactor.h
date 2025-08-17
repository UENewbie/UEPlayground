// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionDataTypes.h"
#include "Interactor.generated.h"


class UInteractable;

UCLASS(ClassGroup=(Custom), BlueprintType, Blueprintable, meta=(BlueprintSpawnableComponent))
class INTERACTIONRUNTIME_API UInteractor : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractor();

protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION(Server, Reliable)
	void ConnectObject();
	UFUNCTION(Server, Reliable)
	void DisconnectObject();
	UFUNCTION(BlueprintCallable)
	bool TryInteraction();
	UFUNCTION()
	void InteractionSuccess();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionScanInterval;
private:
	UFUNCTION()
	void ScanBySightLine();
	
	TObjectPtr<APawn> OwnerPawn;
	TObjectPtr<APlayerController> OwnerController;
	FTimerHandle ScanTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInteractable> InteractableInSight;
	
	
};
