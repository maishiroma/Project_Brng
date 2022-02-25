// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "MainGameOverlay.generated.h"

class AGameState_Main;
class UMain_GameInstance;

/**
 * 
 */
UCLASS()
class BRNG_SOURCE_API UMainGameOverlay : public UUserWidget
{
	GENERATED_BODY()

private:
	
	// Timer Function
	void ClearHUD();

	// Displays the player scores to the screen
	void FormatPlayerScores();

	// Displays the countdown for the players to see
	void DisplayCountdown();

	// Displays the winner of the match
	void DisplayWinner();

	// Ref to GameState
	AGameState_Main* GameStateRef;

	// Timer Handler
	FTimerHandle MemberTimerHandle;

protected:
	
	// Sets up the widget
	virtual void NativeOnInitialized() override;

	// Tick event for widgets
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// Ref to display the countdown text
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Countdown_Text;

	// Ref to the player scores
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* PlayerScores_Text;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Loading_Text;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* Loading_BG;

};
