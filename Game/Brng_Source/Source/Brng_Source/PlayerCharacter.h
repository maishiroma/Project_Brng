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

	// Is the player holding down the shoot button?
	bool isHolding;

	// How long has the player held down the button?
	float currTimeCharging;

	// Current length of time during boomerang recharge
	float currTimeToRecharge;

	// The current direction the player is facing
	int currForwardDirection;

	// The Update method; controls what this class does on each tick
	virtual void Tick(float DeltaSeconds) override;

	// Grabs the player input
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

	// Controls left/right movement
	void MoveHorizontal(float Value);

	// Shoot Boomerang
	void ThrowBoomerang();

	// Shoot a stronger boomerang
	void ThrowPowerBoomerang();

	// Checks if the player has enough energy to throw aa boomerang
	bool CheckIfEnoughEnergy(float cost);

protected:

	// Sets what boomerang blueprint one will use
	UPROPERTY(EditAnywhere, Category = "Shooting")
		TSubclassOf<class ABoomerang> NormalBoomerangClass;

	UPROPERTY(EditAnywhere, Category = "Shooting")
		TSubclassOf<class ABoomerang> PowerBoomerangClass;
	
	// The speed at which the player can throw their boomerang
	UPROPERTY(EditAnywhere, Category = "Shooting")
		float throwSpeed;
	
	// The amount of energy to throw a boomerang
	UPROPERTY(EditAnywhere, Category = "Shooting")
		float throwEnergyCost;

	// The amount of energy recovered during a cooldown
	UPROPERTY(EditAnywhere, Category = "Shooting")
		float throwEnergyRecoverAmount;

	// The amount of energy the player has left
	UPROPERTY(BlueprintReadOnly, Category = "Shooting")
		float currEnergy;
	
	// The max number of energy that the player has to throw boomerangs
	UPROPERTY(BlueprintReadOnly, Category = "Shooting")
		float maxThrowEnergy;

	// How long does the player regen uses of shooting?
	UPROPERTY(EditAnywhere, Category = "Shooting")
		float coolDownTime;

	// How long does it take to throw a power boomerang?
	UPROPERTY(EditAnywhere, Category = "Shooting")
		float timePowerThrow;

	// Defines a range that the variable can take on
	// In this case, the modifier factor cannot go lower than 1.0
	// What is the movement penalty while charging a shot?
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "1.0", ClampMax = "100.0"))
		float chargeMoveSlowFactor;

public:

	// Constructor for this class; sets defaults
	APlayerCharacter();
};
