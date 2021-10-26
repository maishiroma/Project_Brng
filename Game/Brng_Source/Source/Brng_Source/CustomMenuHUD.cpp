// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMenuHUD.h"
#include "CustomSessionButton.h"

// Constructor
bool UCustomMenuHUD::Initialize()
{
	bool success = Super::Initialize();
	if (success == false)
	{
		return false;
	}

	// Initialize Array for helper
	RandomWords.Add(FString("Super"));
	RandomWords.Add(FString("Mega"));
	RandomWords.Add(FString("Ultra"));
	RandomWords.Add(FString("Awesome"));
	RandomWords.Add(FString("Shattering"));
	RandomWords.Add(FString("Amazing"));

	SessionName_Key = TEXT("servername");

	return true;
}

// When called, exits out of the game
void UCustomMenuHUD::QuitGame()
{
	// https://community.gamedev.tv/t/bull-cow-game-exit-functionality/144296
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

// When called, grabs all of the available Sessions
void UCustomMenuHUD::CreateRoomWidgets(APlayerController* currPlayer)
{
	if (SessionResults.Num() > 0)
	{
		for (int32 currIndex = 0; currIndex < SessionResults.Num(); currIndex++)
		{
			if (Session_Widget_Class != nullptr)
			{
				// We create a nee btton widget and set it up 
				UCustomSessionButton* MenuHud = CreateWidget<UCustomSessionButton>(GetWorld(), Session_Widget_Class);
				MenuHud->SetUpButton(SessionName_Key, SessionResults[currIndex]);
				MenuHud->SetOwningPlayer(currPlayer);
				MenuHud->AddToViewport();

				Sessions_VerticalBox->AddChild(MenuHud);
			}
		}

		// This is how you set text
		// https://stackoverflow.com/questions/63099274/how-to-change-text-in-widget-using-c
		Refresh_Text->SetText(FText::FromString(""));
	}
	else
	{
		Refresh_Text->SetText(FText::FromString("No rooms are open! Try again."));
	}
}

// Toggle the given two CanvasPanels to swap visibilities.
// Returns the newly visible panel
UCanvasPanel* UCustomMenuHUD::SetMenuVisability(UCanvasPanel* MenuToHide, UCanvasPanel* MenuToShow)
{
	MenuToHide->SetVisibility(ESlateVisibility::Hidden);
	MenuToShow->SetVisibility(ESlateVisibility::Visible);

	return MenuToShow;
}

// Creates a random room name based on a random word and a double number
// Returns said pointer to name
FString UCustomMenuHUD::GenerateRandomRoomName()
{
	int randNumb = FMath::FRandRange(0, RandomWords.Num());
	int randId = FMath::FRandRange(0, 100);

	return FString("Room-" + RandomWords[randNumb] + "-" + FString::FromInt(randId));
}