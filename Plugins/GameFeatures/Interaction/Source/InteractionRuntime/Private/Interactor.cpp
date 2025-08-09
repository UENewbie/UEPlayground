// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactor.h"

#include "Interactable.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


UInteractor::UInteractor()
{
	PrimaryComponentTick.bCanEverTick = true;
	UActorComponent::SetComponentTickEnabled(false);

	// Interaction DefaultSettings
	InteractionRange = 400.0f;
	InteractionScanInterval = 0.2f;

	InteractableInSight = nullptr;
}


void UInteractor::BeginPlay()
{
	Super::BeginPlay();

	APawn* Owner = Cast<APawn>(GetOwner());
	if (nullptr != Owner)
	{
		OwnerPawn = Owner;
		if (GetWorld())
		{
			GetWorld()->GetTimerManager().SetTimer(ScanTimerHandle, this, &UInteractor::ScanBySightLine, InteractionScanInterval, true);
		}
	}
	
}

void UInteractor::ConnectObject()
{
	if (nullptr != InteractableInSight)
	{
		InteractableInSight->AddInteractor(this);
		InteractableInSight->OnInteraction.AddDynamic(this, &UInteractor::InteractionSuccess);
	}
}

void UInteractor::DisconnectObject()
{
	if (nullptr != InteractableInSight)
	{
		InteractableInSight->RemoveInteractor(this);
		InteractableInSight->OnInteraction.RemoveDynamic(this, &UInteractor::InteractionSuccess);
	}
}

bool UInteractor::TryInteraction()
{
	if (nullptr != InteractableInSight)
	{
		InteractableInSight->OnInteractionRequest();
	}
	return false;
}

void UInteractor::InteractionSuccess()
{
	GEngine->AddOnScreenDebugMessage(-1, 300.f, FColor::Red, TEXT("Interactor::Interaction Success!"));
}

void UInteractor::ScanBySightLine()
{
	UCameraComponent* CameraComponent = OwnerPawn->FindComponentByClass<UCameraComponent>();
	if (nullptr != CameraComponent)
	{
		USpringArmComponent* Arm =  Cast<USpringArmComponent>(OwnerPawn->FindComponentByClass<USpringArmComponent>());
		FVector ForwardVector = CameraComponent->GetForwardVector();
		float ArmLength = 200.f;
		if (nullptr != Arm)
		{
			ArmLength = Arm->TargetArmLength;
		}
		FVector StartLocation = CameraComponent->GetComponentLocation() + (ForwardVector * ArmLength);
		FVector EndLocation = StartLocation + (ForwardVector * InteractionRange);
		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(OwnerPawn.Get());
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 1.0f, 0, 1.0f);
		if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams))
		{
			if (HitResult.GetActor())
			{
				UInteractable* ObjectInSight = HitResult.GetActor()->FindComponentByClass<UInteractable>();
				if (nullptr != ObjectInSight)
				{
					if (InteractableInSight != ObjectInSight)
					{
						if (InteractableInSight)
						{
							DisconnectObject();
						}
						UE_LOG(LogTemp, Log, TEXT("New Interactable Actor Found: %s"), *HitResult.GetActor()->GetName());
						InteractableInSight = ObjectInSight;
						ConnectObject();
					}
				}
				else if (InteractableInSight)
				{
					DisconnectObject();
					InteractableInSight = nullptr;
				}
			}
			else if (InteractableInSight)
			{
				DisconnectObject();
				InteractableInSight = nullptr;
			}
		}
	}
}


