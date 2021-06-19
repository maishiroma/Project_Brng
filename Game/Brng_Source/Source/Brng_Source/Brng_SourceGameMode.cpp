// Copyright Epic Games, Inc. All Rights Reserved.

#include "Brng_SourceGameMode.h"
#include "PlayerCharacter.h"

// Constructorr
ABrng_SourceGameMode::ABrng_SourceGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();	

	// Default values
	RespawnTime = 1.0f;
}

// Start Function
void ABrng_SourceGameMode::BeginPlay()
{
	// Finds and sets all of the spawn locations for the GameMode to use
	UGameplayStatics::GetAllActorsWithTag(this, FName("SpawnLocation"), spawnLocations);
}

// Function that actually respawns and possesses the new character with the passed in controller
void ABrng_SourceGameMode::PossessNewPlayer(AController* controller, FTransform location)
{
	int retries = 0;
	APawn* pawn = nullptr;
	
	// We first attempt to spawn the player in a random location, based on the set spawn locations on the map
	while (pawn == nullptr)
	{
		FTransform randSpawnLoc = spawnLocations[FMath::RandRange(0, spawnLocations.Num() - 1)]->GetActorTransform();
		pawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, randSpawnLoc);
		
		// If we cannot find a valid spawn point after 5 tries, we default to the original player spawn location
		// and force a spawn
		if (retries > 5)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.bNoFail = true;
			pawn = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, location, spawnParams);
		}
		else
		{
			retries++;
		}
	}

	// Once we respawn, we use the spawned pawn to tell the player controller to possess said pawn
	controller->Possess(pawn);
}

// We pass in the controller and location to tell the server where to spawn the character
void ABrng_SourceGameMode::Respawn(AController* controller, FTransform location)
{
	if (HasAuthority())
	{
		// We specify that we have a function we want to bind the following parameters
		RespawnTimerDelegate.BindUFunction(this, FName("PossessNewPlayer"), controller, location);

		// And then invoke said function via a timer
		GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandler, RespawnTimerDelegate, RespawnTime, false);
	}
}