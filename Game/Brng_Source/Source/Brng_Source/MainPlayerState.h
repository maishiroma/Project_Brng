// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Runtime/Engine/Public/Net/UnrealNetwork.h"
#include "MainPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BRNG_SOURCE_API AMainPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	AMainPlayerState();

	UPROPERTY(Replicated)
		int numbWins;
};
