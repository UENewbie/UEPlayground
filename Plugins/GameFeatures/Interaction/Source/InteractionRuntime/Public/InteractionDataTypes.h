
#pragma once

UENUM(BlueprintType)
enum class EInteractionType : uint8
{
	None			UMETA(DisplayName = "None"),
	Instant 		UMETA(DisplayName = "Instant"),
	Hold 			UMETA(DisplayName = "Hold"),
	Toggle			UMETA(DisplayName = "Toggle"),
	Charge			UMETA(DisplayName = "Charge")
};

UENUM(BlueprintType)
enum class EInteractionState : uint8
{
	None				UMETA(DisplayName = "None"),
	Interactable		UMETA(DisplayName = "Interactable"),
	Disabled			UMETA(DisplayName = "Disabled"),
	InProgress			UMETA(DisplayName = "InProgress"),
	Completed			UMETA(DisplayName = "Completed"),
	Failed				UMETA(DisplayName = "Failed")
};