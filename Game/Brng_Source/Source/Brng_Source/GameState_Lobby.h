// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Runtime/Engine/Public/Net/UnrealNetwork.h"
#include "GameState_Lobby.generated.h"

/**
 * 
 */
UCLASS()
class BRNG_SOURCE_API AGameState_Lobby : public AGameState
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Replicated)
		bool HasPlayerQueued;
	
};
