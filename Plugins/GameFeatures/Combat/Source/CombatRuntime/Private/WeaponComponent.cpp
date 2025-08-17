

#include "WeaponComponent.h"


UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	UActorComponent::SetComponentTickEnabled(false);

	OwnerPawn = nullptr;
}


void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	APawn* Owner = Cast<APawn>(GetOwner());
	if (nullptr != Owner)
	{
		OwnerPawn = Owner;
	}
	
}



