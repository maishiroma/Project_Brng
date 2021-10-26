// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/CanvasPanel.h"
#include "FindSessionsCallbackProxy.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CustomMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class BRNG_SOURCE_API UCustomMenuHUD : public UUserWidget
{
	GENERATED_BODY()
	
private:

	// Helper Methods

	UFUNCTION(BlueprintCallable)
		UCanvasPanel* SetMenuVisability(UCanvasPanel* MenuToHide, UCanvasPanel* MenuToShow);

	UFUNCTION(BlueprintCallable)
		FString GenerateRandomRoomName();

	// Main Menu

	UFUNCTION(BlueprintCallable)
		void QuitGame();

	// Join Room

	UFUNCTION(BlueprintCallable)
		void CreateRoomWidgets(APlayerController* currPlayer);

	// Private Vars

	TArray<FString> RandomWords;

protected:
	
	// Class Settings

	UPROPERTY(EditAnywhere, Category = "HUD")
		TSubclassOf<class UCustomSessionButton> Session_Widget_Class;

	// Widget Methods

	virtual bool Initialize() override;

	// Canvas Panels

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UCanvasPanel* MainMenu_Panel;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UCanvasPanel* CreateRoomMenu_Panel;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UCanvasPanel* JoinRoomMenu_Panel;

	// Main Menu
	UPROPERTY(meta = (BindWidget))
		UButton* CreateRoom_Button;

	UPROPERTY(meta = (BindWidget))
		UButton* JoinRoom_Button;

	UPROPERTY(meta = (BindWidget))
		UButton* Quit_Button;

	// Create Room Menu

	UPROPERTY(meta = (BindWidget))
		UButton* RTM_CR_Button;

	UPROPERTY(meta = (BindWidget))
		UButton* CR_Button;

	// Join Room Menu

	UPROPERTY(meta = (BindWidget))
		UButton* Refresh_Button;

	UPROPERTY(meta = (BindWidget))
		UButton* RTM_JR_Button;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Refresh_Text;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UVerticalBox* Sessions_VerticalBox;

	// This requires importing in a specific library
	// https://answers.unrealengine.com/questions/395322/how-to-use-c-session-search-results-with-blueprint.html
	UPROPERTY(BlueprintReadWrite)
		TArray<FBlueprintSessionResult> SessionResults;

public: 

	// The name of the key used to associate with the session room
	UPROPERTY(BlueprintReadOnly)
		FName SessionName_Key;
};
