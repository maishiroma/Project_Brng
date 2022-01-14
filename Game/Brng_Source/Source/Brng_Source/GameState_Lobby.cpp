// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState_Lobby.h"

// Helper Method to label replicated values
void AGameState_Lobby::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGameState_Lobby, HasPlayerQueued);
}