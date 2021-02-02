// Fill out your copyright notice in the Description page of Project Settings.

/* This class will be handling all of the player controls, including movement, attacking, etc.	
 *	This will be heavily based on the auto generated Brng_SourceCharacter class
 *
 * Components that this class will use
 * 
 */


#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h" 
#include "Math/BigInt.h" 
#include "Boomerang.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BRNG_SOURCE_API APlayerCharacter : public APaperCharacter
{
private:
	GENERATED_BODY()

	// The Update method; controls what this class does on each tick
	virtual void Tick(float DeltaSeconds) override;

	// Controls left/right movement
	void MoveHorizontal(float Value);

	// Shoot Boomerang
	void ThrowBoomerang();

	UPROPERTY(EditAnywhere, Category = "Shooting")
	TSubclassOf<class ABoomerang> BoomerangClass;

	// Grabs the player input
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	int currDir;

public:

	// Constructor for this class; sets defaults
	APlayerCharacter();

	UPROPERTY(EditAnywhere, Category = "Shooting")
		float throwSpeed;
	
};
