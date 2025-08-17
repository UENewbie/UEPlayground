
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CorePlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class PLAYGROUNDCORE_API ACorePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ACorePlayerController(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void BeginPlay() override;
	
};
