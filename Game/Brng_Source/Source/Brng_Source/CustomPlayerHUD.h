// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomPlayerHUD.generated.h"

// Need to forward declare this, since this appears before PlayerCharacter in compile order
class APlayerCharacter;

UCLASS()
class BRNG_SOURCE_API UCustomPlayerHUD : public UUserWidget
{
private:
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HUD")
		APlayerCharacter* owningPlayer;
	
};
