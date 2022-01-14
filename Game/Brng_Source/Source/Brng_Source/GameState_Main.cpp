// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState_Main.h"
#include "MyGamePlayerController.h"
#include "Main_GameInstance.h"

// Constructor to set up default variables
AGameState_Main::AGameState_Main()
{
	CurrCountDown = 2;
	HasGameStarted = false;
}

// Countdowwn timer initiator
void AGameState_Main::CountDownTimer()
{
	if (!HasGameStarted)
	{
		if (CurrCountDown <= 0)
		{
			GetWorld()->GetTimerManager().ClearTimer(MemberTimerHandle);
			HasGameStarted = true;
		}

		CurrCountDown--;
	}
}

// Getters
bool AGameState_Main::GetHasGameStarted()
{
	return HasGameStarted;
}

int AGameState_Main::GetCurrCoundDown()
{
	return CurrCountDown;
}

// Method that is called from the blueprint; this checks if the room has the numb of clients connected
// This method fires off a countdowwn timer
void AGameState_Main::CheckIfCanStart()
{
	if (!HasGameStarted && GetWorld()->GetNumPlayerControllers() == Cast<UMain_GameInstance>(GetWorld()->GetGameInstance())->TotalNumberPlayers)
	{
		GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &AGameState_Main::CountDownTimer, 1.0f, true, 2.0f);
	}
}

// Helper Method to label replicated values
void AGameState_Main::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGameState_Main, HasGameStarted);
	DOREPLIFETIME(AGameState_Main, CurrCountDown);
}
