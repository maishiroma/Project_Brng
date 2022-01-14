// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Public/Net/UnrealNetwork.h"
#include "Main_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BRNG_SOURCE_API UMain_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UMain_GameInstance();

	// Number of Players that have conneccted
	UPROPERTY(BlueprintReadWrite, Replicated)
		int TotalNumberPlayers;
};
