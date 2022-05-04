// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Runtime/Engine/Public/Net/UnrealNetwork.h"
#include "GameState_Main.generated.h"

/**
 * 
 */
UCLASS()
class BRNG_SOURCE_API AGameState_Main : public AGameState
{
	GENERATED_BODY()

private:
	// Countdown for game to start
	void StartCountDownTimer();

	// Countdoown for game to end
	void StartFinishCountDownTimer();

	// Timer Handler
	FTimerHandle MemberTimerHandle;

protected:
	
	// The current number that the countdown is at
	UPROPERTY(BlueprintReadOnly, Replicated)
		int CurrCountDown;

	// Has the game started?
	UPROPERTY(BlueprintReadOnly, Replicated)
		bool HasGameStarted;

	// Has the game ended?
	UPROPERTY(BlueprintReadOnly, Replicated)
		bool hasGameConcluded;

	// Stores the name of the winner
	UPROPERTY(BlueprintReadOnly, Replicated)
		FString gameWinnerName;

public:

	// Constructor
	AGameState_Main();

	// Checker to see if the main game has started
	UFUNCTION(BlueprintCallable)
		void CheckIfCanStart();

	// Getters
	bool GetHasGameStarted();
	int GetCurrCoundDown();
	bool GetHasGameConcluded();
	FString GetGameWinnerName();

	// Setters
	void SetGameWinnerName(FString newWinner);

	// The name of the lobby level to load
	UPROPERTY(EditAnywhere, Category = Levels)
		FString LobbyLevel;

	// The number of wins it takes to win the game
	UPROPERTY(EditAnywhere, Category = "Game Loop")
		int reqWins;

};
