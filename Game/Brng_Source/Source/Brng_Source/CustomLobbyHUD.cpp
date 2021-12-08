// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomLobbyHUD.h"

// Sets up Initial Logic for HUD
bool UCustomLobbyHUD::Initialize()
{
	bool success = Super::Initialize();
	if (success == false)
	{
		return false;
	}

	// Allows the player to use the mouse for the GUI
	CurrPlayerController = GetWorld()->GetFirstPlayerController();
	if (CurrPlayerController != nullptr)
	{
		CurrPlayerController->bShowMouseCursor = true;
		CurrPlayerController->bEnableClickEvents = true;
		CurrPlayerController->bEnableMouseOverEvents = true;
	}

	// Sets up some general variables and widgets to be hidden
	Queue_Button->SetVisibility(ESlateVisibility::Hidden);
	Loading_BG->SetVisibility(ESlateVisibility::Hidden);
	Loading_Text->SetVisibility(ESlateVisibility::Hidden);

	return true;
}

void UCustomLobbyHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	int currNumbPlayers = GetWorld()->GetGameState<AGameStateBase>()->PlayerArray.Num();
	FString currPlayerConvert = FString::FromInt(currNumbPlayers);

	No_Players_Text->SetText(FText::FromString("Players: " + currPlayerConvert + "/" + FString::FromInt(MaxNumberPlayers)));
	
	CheckIfEnoughPlayers(currNumbPlayers);
}

// If there's enough players in the lobby, we show this button. Else we hide it
void UCustomLobbyHUD::CheckIfEnoughPlayers(int numbPlayers)
{
	if (GetWorld()->IsServer())
	{
		if (numbPlayers >= 2 && Queue_Button->GetVisibility() == ESlateVisibility::Hidden)
		{
			Queue_Button->SetVisibility(ESlateVisibility::Visible);
		}
		else if (numbPlayers < 2)
		{
			if (Queue_Button->GetVisibility() == ESlateVisibility::Visible)
			{
				Queue_Button->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

// When this is called, the server will tell all clients to follow it to said level
void UCustomLobbyHUD::TravelToMainGame()
{
	if (GetWorld()->IsServer())
	{
		GetWorld()->ServerTravel(LevelToLoad);
	}
}

// When called, will display a loading visual over the client screen to let them know the match is starting
void UCustomLobbyHUD::EnableLoadingVisuals()
{
	Loading_BG->SetVisibility(ESlateVisibility::Visible);
	Loading_Text->SetVisibility(ESlateVisibility::Visible);
}

// Returns a list of client controllers
// Note that only a server can call this method
TArray<APlayerController*> UCustomLobbyHUD::ReturnClientControllers()
{
	TArray<APlayerController*> results;
	if (GetWorld()->IsServer())
	{
		FConstPlayerControllerIterator Iter = GetWorld()->GetPlayerControllerIterator();
		for (Iter; Iter; Iter++)
		{
			APlayerController* currOne = Iter->Get();
			if (currOne != nullptr && !currOne->IsLocalController())
			{
				results.Add(currOne);

			}
		}
	}
	return results;
}

// Button Event to Sent player to main menu
void UCustomLobbyHUD::ReturnToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), MainMenuName);
}