// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomSessionButton.h"

// Sets up the button details once it has been initialized
void UCustomSessionButton::SetUpButton(FName ServerKeyName, FBlueprintSessionResult newData)
{
	if (Session_Name != nullptr)
	{
		FString result;
		bool isValid = newData.OnlineResult.Session.SessionSettings.Get(ServerKeyName, result);

		if (isValid)
		{
			Session_Name->SetText(FText::FromString(result));
			SessionData = newData;
		}
		else
		{
			Session_Name->SetText(FText::FromString("New Room Name"));
		}
	}
}
