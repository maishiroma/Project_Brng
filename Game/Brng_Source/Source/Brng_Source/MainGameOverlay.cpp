// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameOverlay.h"
#include "GameState_Main.h"
#include "MainPlayerState.h"

// By default, sets up the UI values
void UMainGameOverlay::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Countdown_Text->SetText(FText::FromString(""));

	// Wee also grab the GameState as a reference
	if (GameStateRef == nullptr)
	{
		GameStateRef = Cast<AGameState_Main>(GetWorld()->GetGameState());
	}
}

// Every tick, we update the values of these UI elements
void UMainGameOverlay::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	DisplayCountdown();
	FormatPlayerScores();
}

// Method to display the Game Countdown
void UMainGameOverlay::DisplayCountdown()
{
	if (GameStateRef != nullptr)
	{
		if (GameStateRef->GetHasGameStarted() == false)
		{
			switch (GameStateRef->GetCurrCoundDown())
			{
				case 2:
					Countdown_Text->SetText(FText::FromString("Round Something!"));
					break;
				case 1:
					Countdown_Text->SetText(FText::FromString("Ready..."));
					break;
				case 0:
					Countdown_Text->SetText(FText::FromString("FIGHT!"));
					GetWorld()->GetTimerManager().SetTimer(MemberTimerHandle, this, &UMainGameOverlay::ClearHUD, 0.5f, false);
					break;
				default:
					break;
			}
		}
	}
}

// Method to display player scores
void UMainGameOverlay::FormatPlayerScores()
{
	if (GameStateRef != nullptr)
	{
		FString result = "";
		for (APlayerState* curr : GameStateRef->PlayerArray)
		{
			// Scores should be local to the current player
			if (Cast<AMainPlayerState>(curr) != nullptr)
			{
				result += curr->GetPlayerName() + ": " + FString::FromInt(Cast<AMainPlayerState>(curr)->numbWins) + "\t\t";
			}
		}
		PlayerScores_Text->SetText(FText::FromString(result));
	}
}

// We clear out the countdown text
void UMainGameOverlay::ClearHUD()
{
	GetWorld()->GetTimerManager().ClearTimer(MemberTimerHandle);
	Countdown_Text->SetText(FText::FromString(""));
}