// Copyright Epic Games, Inc. All Rights Reserved.

#include "PawnControllerGameMode.h"
#include "PawnControllerCharacter.h"
#include "UObject/ConstructorHelpers.h"

APawnControllerGameMode::APawnControllerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
