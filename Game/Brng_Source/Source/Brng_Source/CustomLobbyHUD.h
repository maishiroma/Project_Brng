// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameState.h"
#include "CustomLobbyHUD.generated.h"

/**
 * The idea for this widget goes like this:
 *	1. Players are entered into a lobby when they join a room. 
 *  2. The host of a room needs to wait for players to join them
 *  3. When a player joins the lobby, they need to queue up for a game
 *  4. Once all connected players queued up, the host can then start the game
 *  5. Anytime a player joins, they can leave the room
 */
UCLASS()
class BRNG_SOURCE_API UCustomLobbyHUD : public UUserWidget
{
	GENERATED_BODY()

protected:

	// Override Constructor
	virtual bool Initialize() override;

	// Tick event for widgets
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// UI Widget Refs
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Queue_Button;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Exit_Button;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Queue_Button_Text;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* No_Players_Text;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Loading_Text;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* Loading_BG;

	// Button Events
	UFUNCTION(BlueprintCallable)
		void ReturnToMainMenu();

	UFUNCTION(BlueprintCallable)
		TArray<APlayerController*> ReturnClientControllers();

	// Helper Methods
	void CheckIfEnoughPlayers(int numbPlayers);

	UFUNCTION(BlueprintCallable)
		void TravelToMainGame();

	UFUNCTION(BlueprintCallable)
		void EnableLoadingVisuals();

	// Saves ref to current player controller
	UPROPERTY(BlueprintReadOnly)
		APlayerController* CurrPlayerController;

public:

	// Allows one to change the name of the menu to navigate torwards
	UPROPERTY(EditAnywhere, Category = UI)
		FName MainMenuName;

	UPROPERTY(EditAnywhere, Category = UI, meta = (UIMin = 2, UIMax = 4))
		int MaxNumberPlayers;
	
	UPROPERTY(EditAnywhere, Category = Levels)
		FString LevelToLoad;
};
