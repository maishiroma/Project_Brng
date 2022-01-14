// Fill out your copyright notice in the Description page of Project Settings.


#include "Main_GameInstance.h"

UMain_GameInstance::UMain_GameInstance()
{
	TotalNumberPlayers = 0;
}

// Helper Method to label replicated values
void UMain_GameInstance::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMain_GameInstance, TotalNumberPlayers);
}
