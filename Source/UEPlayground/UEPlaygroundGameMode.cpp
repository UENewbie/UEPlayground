// Copyright Epic Games, Inc. All Rights Reserved.

#include "UEPlaygroundGameMode.h"
#include "UEPlaygroundCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUEPlaygroundGameMode::AUEPlaygroundGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
