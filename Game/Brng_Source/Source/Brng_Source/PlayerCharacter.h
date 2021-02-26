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

	// Sets what boomerang blueprint one will use
	UPROPERTY(EditAnywhere, Category = "Shooting")
		TSubclassOf<class ABoomerang> NormalBoomerangClass;

	UPROPERTY(EditAnywhere, Category = "Shooting")
		TSubclassOf<class ABoomerang> PowerBoomerangClass;

	// Is the player holding down the shoot button?
	bool isHolding;

	// How long has the player held down the button?
	float currTimeCharging;

	// Current length of time during boomerang recharge
	float currTimeToRecharge;

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

protected:
	
	// The current direction the player is facing
	UPROPERTY(VisibleAnywhere, Category = "Movement")
		int currDir;

	// The max number of energy that the player has to throw boomerangs
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Shooting")
		float maxThrowEnergy;

public:

	// Constructor for this class; sets defaults
	APlayerCharacter();

	// The speed at which the player can throw their boomerang
	UPROPERTY(EditAnywhere, Category = "Shooting")
		float throwSpeed;

	// How long does it take to throw a power boomerang?
	UPROPERTY(EditAnywhere, Category = "Shooting")
		float timeToCharge;
		
	// How long does the player regen uses of shooting?
	UPROPERTY(EditAnywhere, Category = "Shooting")
		float timeOfCooldown;

	// The amount of energy to throw a boomerang
	UPROPERTY(EditAnywhere, Category = "Shooting")
		float throwEnergyCost;
	
	// The amount of energy recovered during a cooldown
	UPROPERTY(EditAnywhere, Category = "Shooting")
		float throwEnergyRecoverAmount;

	// The amount of energy the player has left
	UPROPERTY(BlueprintReadOnly, Category = "Shooting")
		float currEnergy;

};
