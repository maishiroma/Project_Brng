// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Runtime/Engine/Public/Net/UnrealNetwork.h"
#include "GameState_Main.generated.h"

/**
 * 
 */
UCLASS()
class BRNG_SOURCE_API AGameState_Main : public AGameStateBase
{
	GENERATED_BODY()

private:
	// Timer Function
	void CountDownTimer();

	// Timer Handler
	FTimerHandle MemberTimerHandle;

protected:
	
	// The current number that the countdown is at
	UPROPERTY(BlueprintReadOnly, Replicated)
		int CurrCountDown;

	// Has the game started?
	UPROPERTY(BlueprintReadOnly, Replicated)
		bool HasGameStarted;

public:

	// Constructor
	AGameState_Main();

	// Checker to see if the main game has started
	UFUNCTION(BlueprintCallable)
		void CheckIfCanStart();

	// Getters
	bool GetHasGameStarted();
	int GetCurrCoundDown();

};
