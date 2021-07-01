// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"
#include "Engine/EngineTypes.h" 
#include "GameFramework/GameModeBase.h"
#include "Containers/Array.h"
#include "Brng_SourceGameMode.generated.h"

/**
 * The GameMode defines the game being played. It governs the game rules, scoring, what actors
 * are allowed to exist in this game type, and who may enter the game.
 *
 */
UCLASS(minimalapi)
class ABrng_SourceGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:

	// Used to pass in parameters to a delayed function
	FTimerDelegate RespawnTimerDelegate;

	// Used to handle delays
	// https://www.tomlooman.com/using-timers-in-ue4/
	FTimerHandle RespawnTimerHandler;

	// Holds all of the spawn locations that players can spawn to
	// Use the actor blueprint, SppawnLocation_BP to set more
	UPROPERTY(VisibleAnywhere)
		TArray<AActor*> spawnLocations;

	// Start Function; Runs at the start of the game
	virtual void BeginPlay() override;

	// Creates and Possess the spawned pawn with the given controller
	UFUNCTION()
		void PossessNewPlayer(AController* controller, FTransform location);

protected:

	// How long does it take for the player to respawn
	UPROPERTY(EditAnywhere, Category = "Respawn")
		float RespawnTime;

public:
	ABrng_SourceGameMode();

	// Server Function that will respawn in the player after death
	void Respawn(AController* controller, FTransform location);
};
