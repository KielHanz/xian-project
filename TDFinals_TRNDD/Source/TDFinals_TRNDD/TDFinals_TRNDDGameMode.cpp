// Copyright Epic Games, Inc. All Rights Reserved.

#include "TDFinals_TRNDDGameMode.h"
#include "TDFinals_TRNDDCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATDFinals_TRNDDGameMode::ATDFinals_TRNDDGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
