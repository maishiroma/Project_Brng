// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

APlayerCharacter::APlayerCharacter()
{
	// https://answers.unrealengine.com/questions/413007/whats-with-the-pitch-yaw-and-roll.html
	// X Axis = Roll; Y Axis = Pitch; Z Axis = Yaw

	// We only want to make sure the Z axis matches with the PlayerController
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the default facing direction
	currForwardDirection = 1;

	// Sets all other variables
	chargeMoveSlowFactor = 2.0f;
	isHolding = false;
	currTimeCharging = 0.0f;
	currTimeToRecharge = 0.0f;

	// This value is set to 100.0f because of how Unreal's Progress Bar UI works with values between 0 and 1
	maxThrowEnergy = 100.0f;
	currEnergy = maxThrowEnergy;
}

// Handles timed events
void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (isHolding)
	{
		// If we are holding down the power boomerang key, we increment the time
		currTimeCharging += DeltaSeconds;
	}

	// Recharge boomerange throw energy
	if (currEnergy < maxThrowEnergy)
	{
		currTimeToRecharge += DeltaSeconds;

		if (currTimeToRecharge >= coolDownTime)
		{
			currEnergy = FMath::Clamp(currEnergy + throwEnergyRecoverAmount, 0.0f, maxThrowEnergy);
			currTimeToRecharge = 0.0f;
		}
	}
}

// Handles's the player movement
void APlayerCharacter::MoveHorizontal(float Value)
{
	// If the player is charging, they slow down drastically
	if (Value != 0.0f)
	{
		// We need to create an instance of this first so we can use the sign function
		TBigInt<64, true> converter = FMath::FloorToInt(Value);
		currForwardDirection = converter.Sign();
	}

	if (isHolding == false)
	{
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
	}
	else
	{
		AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value / chargeMoveSlowFactor);
	}
}

// Shoots the boomerang outwards
void APlayerCharacter::ThrowBoomerang()
{
	if (NormalBoomerangClass != nullptr && CheckIfEnoughEnergy(throwEnergyCost))
	{
		// Places the Boomerang in front of the player to start its movement
		FTransform BoomerangSpawnTransform;
		BoomerangSpawnTransform.SetLocation((currForwardDirection * GetActorForwardVector()) * 100.0f + GetActorLocation());
		BoomerangSpawnTransform.SetRotation(GetActorRotation().Quaternion());
		
		// In order to set the movement direction of the projectile dynamically, we need to use this function
		ABoomerang* instance = GetWorld()->SpawnActorDeferred<ABoomerang>(NormalBoomerangClass, BoomerangSpawnTransform);
		instance->Initialize(throwSpeed, currForwardDirection);

		// Once we are done, we then need to tell the object to finish spawning
		UGameplayStatics::FinishSpawningActor(instance, BoomerangSpawnTransform);

		currEnergy -= throwEnergyCost;
	}
	
}

// Handles the logic for power boomerangs
void APlayerCharacter::ThrowPowerBoomerang()
{
	if (PowerBoomerangClass != nullptr)
	{
		if (isHolding == true)
		{
			if (currTimeCharging >= timePowerThrow && CheckIfEnoughEnergy(throwEnergyCost * 2.0f))
			{
				// If we held the button long enough, we will throw a strong boomerang
				// Places the Boomerang in front of the player to start its movement
				FTransform BoomerangSpawnTransform;
				BoomerangSpawnTransform.SetLocation((currForwardDirection * GetActorForwardVector()) * 100.0f + GetActorLocation());
				BoomerangSpawnTransform.SetRotation(GetActorRotation().Quaternion());

				// In order to set the movement direction of the projectile dynamically, we need to use this function
				ABoomerang* instance = GetWorld()->SpawnActorDeferred<ABoomerang>(PowerBoomerangClass, BoomerangSpawnTransform);
				instance->Initialize(throwSpeed * 2.0f, currForwardDirection);

				// Once we are done, we then need to tell the object to finish spawning
				UGameplayStatics::FinishSpawningActor(instance, BoomerangSpawnTransform);

				// For now, we double the energe cost to throw a power boomerang
				currEnergy -= 2.0f * throwEnergyCost;
			}

			// Regardless if the player held long enough or had enough energy, we reset the stats
			isHolding = false;
			currTimeCharging = 0.0f;
		}
		else
		{
			// The player is now holding onto the button
			isHolding = true;
		}
	}
}

// Binds the player controls to specific methods and keys
// Make sure parammeters don't match the name of the class
void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	playerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	playerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	playerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveHorizontal);

	playerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::ThrowBoomerang);
	
	playerInputComponent->BindAction("Fire_2", IE_Pressed, this, &APlayerCharacter::ThrowPowerBoomerang);
	playerInputComponent->BindAction("Fire_2", IE_Released, this, &APlayerCharacter::ThrowPowerBoomerang);
}

// Checks if the player has enough energy to throw a boomerang
// Returns true if it can
// Helper method
bool APlayerCharacter::CheckIfEnoughEnergy(float cost)
{
	if (currEnergy - cost < 0.0f)
	{
		return false;
	}
	return true;
}