// Copyright Epic Games, Inc. All Rights Reserved.

#include "Brng_SourceGameMode.h"
#include "PlayerCharacter.h"
#include "GameState_Main.h"
#include "MainPlayerState.h"

// Constructor
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

	if (GameStateRef == nullptr)
	{
		GameStateRef = Cast<AGameState_Main>(GetWorld()->GetGameState());
	}
}

// Tick that runs code on every tick
void ABrng_SourceGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// We check to see if we have a winner during the match
	if (GameStateRef != nullptr && GameStateRef->GetHasGameConcluded() == false)
	{
		for (APlayerState* curr : GameStateRef->PlayerArray)
		{
			AMainPlayerState* playerstate = Cast<AMainPlayerState>(curr);
			if (playerstate != nullptr && playerstate->numbWins == GameStateRef->reqWins)
			{
				GameStateRef->SetGameWinnerName(playerstate->GetPlayerName());
				break;
			}
		}
	}
}


// Function that actually respawns and possesses the new character with the passed in controller
void ABrng_SourceGameMode::PossessNewPlayer(AController* controller, FTransform location)
{
	int retries = 0;
	APlayerCharacter* newSpawnedCharacter = nullptr;
	
	// We first attempt to spawn the player in a random location, based on the set spawn locations on the map
	while (newSpawnedCharacter == nullptr)
	{
		FTransform randSpawnLoc = spawnLocations[FMath::RandRange(0, spawnLocations.Num() - 1)]->GetActorTransform();
		newSpawnedCharacter = GetWorld()->SpawnActor<APlayerCharacter>(DefaultPawnClass, randSpawnLoc);
		
		// If we cannot find a valid spawn point after 5 tries, we default to the original player spawn location
		// and force a spawn
		if (retries > 5)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.bNoFail = true;
			newSpawnedCharacter = GetWorld()->SpawnActor<APlayerCharacter>(DefaultPawnClass, location, spawnParams);
		}
		else
		{
			retries++;
		}
	}

	// Once we respawn, we use the spawned pawn to tell the player controller to possess said pawn
	controller->Possess(newSpawnedCharacter);

	// For some reason, the HUD gets unconfigured for the host player
	// so we need to make sure we reconfigure the HUD for them whenever they respawn
	newSpawnedCharacter->ReConfigureHUD();
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