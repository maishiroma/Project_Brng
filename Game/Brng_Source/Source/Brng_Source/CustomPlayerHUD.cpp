// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerHUD.h"

// By default, sets up the UI values
void UCustomPlayerHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	ResetHUD();
}

// Every tick, we update the values of these UI elements
void UCustomPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (owningPlayer != nullptr)
	{
		UpdateHealthMeter();
		UpdateStaminaMeter();
	}
}

// We update the player health based on their current values
void UCustomPlayerHUD::UpdateHealthMeter()
{
	if (playerHealth != nullptr)
	{
		float unboundResult = owningPlayer->GetCurrHealth() / owningPlayer->GetMaxHealth();
		float results = FMath::Clamp(unboundResult, 0.0f, 1.0f);
		playerHealth->SetPercent(results);
	}
}

// We update the player stamina based on their current values
void UCustomPlayerHUD::UpdateStaminaMeter()
{
	if (playerStamina != nullptr)
	{
		float unboundResult = owningPlayer->GetCurrEnergy() / owningPlayer->GetMaxEnergy();
		float results = FMath::Clamp(unboundResult, 0.0f, 1.0f);
		playerStamina->SetPercent(results);
	}
}

// Helper method to reset the values of the HUD back to their default values
void UCustomPlayerHUD::ResetHUD()
{
	if (playerHealth != nullptr)
	{
		playerHealth->SetPercent(1.0f);
	}

	if (playerStamina != nullptr)
	{
		playerStamina->SetPercent(1.0f);
	}
}