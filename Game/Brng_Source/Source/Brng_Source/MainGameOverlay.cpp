// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameOverlay.h"
#include "GameState_Main.h"

// By default, sets up the UI values
void UMainGameOverlay::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	Countdown_Text->SetText(FText::FromString(""));

	if (GameStateRef == nullptr)
	{
		GameStateRef = Cast<AGameState_Main>(GetWorld()->GetGameState());
	}
}

// Every tick, we update the values of these UI elements
void UMainGameOverlay::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
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

// We clear out the countdown text
void UMainGameOverlay::ClearHUD()
{
	GetWorld()->GetTimerManager().ClearTimer(MemberTimerHandle);
	Countdown_Text->SetText(FText::FromString(""));
}