// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "FindSessionsCallbackProxy.h"
#include "OnlineKeyValuePair.h"
#include "CustomSessionButton.generated.h"

/**
 * 
 */
UCLASS()
class BRNG_SOURCE_API UCustomSessionButton : public UUserWidget
{
	GENERATED_BODY()

protected:

	// Widget Articles

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Session_Name;

	// Widget Information

	UPROPERTY(BlueprintReadOnly)
		FBlueprintSessionResult SessionData;

public:

	// Sets up the button details after it has been created
	void SetUpButton(FName ServerKeyName, FBlueprintSessionResult newData);
};
