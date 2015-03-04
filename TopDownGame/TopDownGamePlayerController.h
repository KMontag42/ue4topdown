// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "FPSProjectile.h"
#include "TopDownGameCharacter.h"
#include "TopDownGamePlayerController.generated.h"

UCLASS()
class ATopDownGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATopDownGamePlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface
    
    UFUNCTION()
    void MoveForward(float AxisValue);
    UFUNCTION()
    void MoveRight(float AxisValue);
    UFUNCTION()
    void Jump();
    UFUNCTION()
    void ShootProjectile();
};


