// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MainGameOverlay.generated.h"

class AGameState_Main;

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
};
