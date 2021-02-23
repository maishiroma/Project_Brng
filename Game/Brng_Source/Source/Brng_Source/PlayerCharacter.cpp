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
	currDir = 1;
	isHolding = false;
	currTimeCharging = 0.0f;
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (isHolding)
	{
		// If we are holding down the power boomerang key, we increment the time
		currTimeCharging += DeltaSeconds;
	}
}

// Handles's the player movement
void APlayerCharacter::MoveHorizontal(float Value)
{
	if (Value != 0.0f)
	{
		// We need to create an instance of this first so we can use the sign function
		TBigInt<64, true> converter = FMath::FloorToInt(Value);
		currDir = converter.Sign();
	}

	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

// Shoots the boomerang outwards
void APlayerCharacter::ThrowBoomerang()
{
	if (NormalBoomerangClass != nullptr)
	{
		// Places the Boomerang in front of the player to start its movement
		FTransform BoomerangSpawnTransform;
		BoomerangSpawnTransform.SetLocation((currDir * GetActorForwardVector()) * 100.0f + GetActorLocation());
		BoomerangSpawnTransform.SetRotation(GetActorRotation().Quaternion());
		
		// In order to set the movement direction of the projectile dynamically, we need to use this function
		ABoomerang* instance = GetWorld()->SpawnActorDeferred<ABoomerang>(NormalBoomerangClass, BoomerangSpawnTransform);
		instance->Initialize(throwSpeed, currDir);

		// Once we are done, we then need to tell the object to finish spawning
		UGameplayStatics::FinishSpawningActor(instance, BoomerangSpawnTransform);
	}
	
}

void APlayerCharacter::ThrowPowerBoomerang()
{
	if (PowerBoomerangClass != nullptr && this->GetVelocity().IsNearlyZero() == true)
	{
		// Toggles between true and false whenever this is pressed and released (as long as the player is not moving)
		isHolding = !isHolding;

		// If the player just released the button
		if (isHolding == false)
		{
			// If we held the button long enough, we will throw a strong boomerang
			if (currTimeCharging >= timeToCharge)
			{
				// Places the Boomerang in front of the player to start its movement
				FTransform BoomerangSpawnTransform;
				BoomerangSpawnTransform.SetLocation((currDir * GetActorForwardVector()) * 100.0f + GetActorLocation());
				BoomerangSpawnTransform.SetRotation(GetActorRotation().Quaternion());

				// In order to set the movement direction of the projectile dynamically, we need to use this function
				ABoomerang* instance = GetWorld()->SpawnActorDeferred<ABoomerang>(PowerBoomerangClass, BoomerangSpawnTransform);
				instance->Initialize(throwSpeed * 2.0f, currDir);

				// Once we are done, we then need to tell the object to finish spawning
				UGameplayStatics::FinishSpawningActor(instance, BoomerangSpawnTransform);
			}
			currTimeCharging = 0.0f;
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
	
	playerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::ThrowPowerBoomerang);
	playerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::ThrowPowerBoomerang);
}