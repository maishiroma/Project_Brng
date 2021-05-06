// Fill out your copyright notice in the Description page of Project Settings.

// Player Controllers should hold persistent things, unlike characters

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BRNG_SOURCE_API AMyGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	// Constructor for this class; sets defaults
	AMyGamePlayerController();
};
