// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState_Main.h"
#include "MyGamePlayerController.h"
#include "Main_GameInstance.h"

// Constructor to set up default variables
AGameState_Main::AGameState_Main()
{
	CurrCountDown = 2;
	HasGameStarted = false;
	hasGameConcluded = false;
	gameWinnerName = "";
}

// Countdowwn timer initiator for game to start
void AGameState_Main::StartCountDownTimer()
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

// Countdown timer for game to completly end
void AGameState_Main::StartFinishCountDownTimer()
{
	if (hasGameConcluded)
	{
		if (CurrCountDown <= 0 && GetWorld()->IsServer())
		{
			GetWorld()->ServerTravel(LobbyLevel);
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

bool AGameState_Main::GetHasGameConcluded()
{
	return hasGameConcluded;
}

FString AGameState_Main::GetGameWinnerName()
{
	return gameWinnerName;
}

// Setters
void AGameState_Main::SetGameWinnerName(FString newWinner)
{
	if (hasGameConcluded == false)
	{
		gameWinnerName = newWinner;
		hasGameConcluded = true;
		
		// Once we get a winner, we display a new HUD and transition back to the lobby
		CurrCountDown = 2;
		GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &AGameState_Main::StartFinishCountDownTimer, 1.0f, true, 2.0f);
	}
}

// Method that is called from the blueprint; this checks if the room has the numb of clients connected
// This method fires off a countdowwn timer
void AGameState_Main::CheckIfCanStart()
{
	if (!HasGameStarted && GetWorld()->GetNumPlayerControllers() == Cast<UMain_GameInstance>(GetWorld()->GetGameInstance())->TotalNumberPlayers)
	{
		GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &AGameState_Main::StartCountDownTimer, 1.0f, true, 2.0f);
	}
}

// Helper Method to label replicated values
void AGameState_Main::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGameState_Main, hasGameConcluded);
	DOREPLIFETIME(AGameState_Main, gameWinnerName);
	DOREPLIFETIME(AGameState_Main, HasGameStarted);
	DOREPLIFETIME(AGameState_Main, CurrCountDown);
}
