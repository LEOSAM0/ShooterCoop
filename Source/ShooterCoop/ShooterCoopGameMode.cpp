// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShooterCoopGameMode.h"
#include "ShooterCoopCharacter.h"
#include "UObject/ConstructorHelpers.h"

AShooterCoopGameMode::AShooterCoopGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
