// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "PlayerCharacter.h"
#include "CustomPlayerHUD.generated.h"

// Need to forward declare this, since this appears before PlayerCharacter in compile order
class APlayerCharacter;

UCLASS()
class BRNG_SOURCE_API UCustomPlayerHUD : public UUserWidget
{
private:
	GENERATED_BODY()

	// Update Player Health
	void UpdateHealthMeter();

	// Update Player Stamina
	void UpdateStaminaMeter();

protected:

	// Sets up the widget
	virtual void NativeOnInitialized() override;

	// Tick event for widgets
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// Initialize and sets up these Components as widgets
	// Note that the meta tag tells the blueprint to bind any placed widget on the UI to
	// this value
	// Also, this variable name NEEDS to be the same name as the widget itself!
	UPROPERTY(meta = (BindWidget))
		UProgressBar* playerHealth;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* playerStamina;

public:

	// Resets HUD values
	void ResetHUD();

	// Property to grab and utilize the currently associated player
	UPROPERTY(BlueprintReadOnly, Category = "HUD")
		APlayerCharacter* owningPlayer;
	
};
