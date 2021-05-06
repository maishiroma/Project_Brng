// Copyright Epic Games, Inc. All Rights Reserved.

#include "Brng_SourceGameMode.h"
#include "Brng_SourceCharacter.h"

ABrng_SourceGameMode::ABrng_SourceGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = ABrng_SourceCharacter::StaticClass();	
}
