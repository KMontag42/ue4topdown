// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TopDownGame.h"
#include "TopDownGameGameMode.h"
#include "TopDownGamePlayerController.h"
#include "TopDownGameCharacter.h"

ATopDownGameGameMode::ATopDownGameGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// use our custom PlayerController class
	PlayerControllerClass = ATopDownGamePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}