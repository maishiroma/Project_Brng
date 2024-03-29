// Fill out your copyright notice in the Description page of Project Settings.

// To reference any calls to any external methods, place their header file here
// THIS is how you do ext deps
#include "PlayerCharacter.h"
#include "Boomerang.h"
#include "Multi_Camera.h"
#include "CustomPlayerHUD.h"
#include "Brng_SourceGameMode.h"
#include "GameState_Main.h"


APlayerCharacter::APlayerCharacter()
{	
	bReplicates = true;
	
	// Player Values
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
	isAlive = true;
	isHolding = false;
	currTimeCharging = 0.0f;
	currTimeToRecharge = 0.0f;

	// These values are set to 100.0f because of how Unreal's Progress Bar UI works with values between 0 and 1
	maxThrowEnergy = 100.0f;
	currEnergy = maxThrowEnergy;
	maxHealth = 100.0f;
	currHealth = maxHealth;
}

// Handles start events
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Because BeginPlay is ran multiple times in a multiplayer game, we want to make sure some things are only spawned once
	// As such, we can use IsLocallyControlled to make sure that only one thing is created
	// https://answers.unrealengine.com/questions/396227/hud-added-multiple-times-in-multiplayer-network.html
	if (IsLocallyControlled()) {
		
		// Spawns and sets the camera position at the current player
		if (PlayerCamClass != nullptr)
		{
			// Sets the parent object at origin
			FTransform defaultPos;
			defaultPos.SetLocation(FVector(0, 0, 0));
			PlayerCam = GetWorld()->SpawnActor<AMulti_Camera>(PlayerCamClass, defaultPos);

			// We set the actual camera, which is a child component of the camera we pass in to be the new pos that we passed in
			USceneComponent* camera = Cast<USceneComponent>(PlayerCam->GetComponentByClass(UCameraComponent::StaticClass()));
			camera->SetRelativeLocation(PlayerCameraPosition);

			GetWorld()->GetFirstPlayerController()->SetViewTargetWithBlend(PlayerCam);
		}

		// Spawns the HUD and associates it with the current player
		// https://answers.unrealengine.com/questions/440581/how-to-create-a-umg-widget-instance-using-c.html
		ReConfigureHUD();
	}

	if (GameStateRef == nullptr)
	{
		GameStateRef = Cast<AGameState_Main>(GetWorld()->GetGameState());
	}

	// Setting up the respawn logic
	spawnLocation.SetLocation(GetActorLocation());
	spawnLocation.SetRotation(FQuat(GetActorRotation()));
}

// Handles timed events
void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (DisableMovement == true)
	{
		// If we disabled movement initially (or whenever) it can only be set back if the 
		// game state gets HasGameStarted set back to true
		
		if (GameStateRef != nullptr && GameStateRef->GetHasGameStarted())
		{
			DisableMovement = false;
		}
	}
	else if (CheckIfActionable())
	{
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
}


// Getters
float APlayerCharacter::GetCurrHealth() const
{
	return currHealth;
}

float APlayerCharacter::GetCurrEnergy() const
{
	return currEnergy;
}

float APlayerCharacter::GetMaxEnergy() const
{
	return maxThrowEnergy;
}

float APlayerCharacter::GetMaxHealth() const
{
	return maxHealth;
}

bool APlayerCharacter::GetIsAlive() const
{
	return isAlive;
}

bool APlayerCharacter::CheckIfActionable()
{
	if (GameStateRef != nullptr)
	{
		// If we are in the main game, we check if the game is currently being played
		// otherwise we are not considered actionable
		if (!GameStateRef->GetHasGameConcluded() && GameStateRef->GetHasGameStarted())
		{
			return isAlive && !DisableMovement;
		}
		return false;
	}
	// If the state is a nullptr, we just have the standard logic in place
	return isAlive && !DisableMovement;
}

void APlayerCharacter::ReConfigureHUD()
{
	if (PlayerHUDClass != nullptr)
	{
		PlayerHUD = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);

		// This allows us to do specific things with specific type of HUDs
		if (PlayerHUD->IsA(UCustomPlayerHUD::StaticClass()))
		{
			Cast<UCustomPlayerHUD>(PlayerHUD)->owningPlayer = this;
		}
		
		PlayerHUD->AddToViewport();
	}

	if (MainGameOverlayClass != nullptr)
	{
		MainGameHUD = CreateWidget<UUserWidget>(GetWorld(), MainGameOverlayClass);
		MainGameHUD->AddToViewport();
	}
}

// Using the passed in movement, we turn the player around
void APlayerCharacter::TurnPlayer(float MoveDir)
{
	if (CheckIfActionable()) 
	{
		// We need to create an instance of this first so we can use the sign function
		TBigInt<64, true> converter = FMath::FloorToInt(MoveDir);
		currForwardDirection = converter.Sign();
	}
}

// Validates that the turn was correct
bool APlayerCharacter::Server_TurnPlayer_Validate(float MoveDir)
{
	return true;
}

// Server RPC to call this onto the server as well
void APlayerCharacter::Server_TurnPlayer_Implementation(float MoveDir)
{
	if (CheckIfActionable())
	{
		TBigInt<64, true> converter = FMath::FloorToInt(MoveDir);
		currForwardDirection = converter.Sign();
	}
}

// Handles's the player movement
void APlayerCharacter::MoveHorizontal(float Value)
{
	if (CheckIfActionable())
	{
		// If the player is charging, they slow down drastically
		if (Value != 0.0f)
		{
			if (!HasAuthority())
			{
				// In Client
				Server_TurnPlayer(Value);
			}
			else
			{
				// In Server
				TurnPlayer(Value);
			}
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
}

// When invoked, disassociates the boomerang with the player
void APlayerCharacter::SetCurrBoomerangNull()
{
	if (currBoomerang != nullptr)
	{
		currBoomerang = nullptr;
	}
}

// Shoots the boomerang outwards
// To replicate, make sure replicates and replicate movement are toggled in BP (server -> client)
void APlayerCharacter::ThrowBoomerang()
{
	if (CheckIfActionable())
	{
		if (NormalBoomerangClass != nullptr && CheckIfEnoughEnergy(throwEnergyCost))
		{
			// Places the Boomerang in front of the player to start its movement
			FTransform BoomerangSpawnTransform;
			BoomerangSpawnTransform.SetLocation((currForwardDirection * GetActorForwardVector()) * 100.0f + GetActorLocation());
			BoomerangSpawnTransform.SetRotation(GetActorRotation().Quaternion());

			// Checks if the current cliet is a server instance. If not, we want to call the servr RPC
			// We can also do GetWorld()->IsServer()
			// Another way is GetLocalRole() > ROLE_AUTHORITY
			if (!HasAuthority())
			{
				// On Client
				Server_ThrowBoomerang(BoomerangSpawnTransform);
			}
			else
			{
				// On Server
				// In order to set the movement direction of the projectile dynamically, we need to use this function
				currBoomerang = GetWorld()->SpawnActorDeferred<ABoomerang>(NormalBoomerangClass, BoomerangSpawnTransform);
				currBoomerang->Initialize(throwSpeed, currForwardDirection, this, false);

				// Once we are done, we then need to tell the object to finish spawning
				UGameplayStatics::FinishSpawningActor(currBoomerang, BoomerangSpawnTransform);
			}

			currEnergy -= throwEnergyCost;
		}
	}
	
}

// Validate the Server RPC call of throwing a boomerang
bool APlayerCharacter::Server_ThrowBoomerang_Validate(FTransform boomerangSpawnTransform)
{
	return true;
}

// Server RPC Function; This spawns the projectile onto the server
void APlayerCharacter::Server_ThrowBoomerang_Implementation(FTransform boomerangSpawnTransform)
{
	if (CheckIfActionable())
	{
		currBoomerang = GetWorld()->SpawnActorDeferred<ABoomerang>(NormalBoomerangClass, boomerangSpawnTransform);
		currBoomerang->Initialize(throwSpeed, currForwardDirection, this, false);
		UGameplayStatics::FinishSpawningActor(currBoomerang, boomerangSpawnTransform);
	}
}

// Handles the logic for power boomerangs
void APlayerCharacter::ThrowPowerBoomerang()
{
	if (CheckIfActionable())
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

					// Server RPC to make sure clients spawn the boomerang on the server
					if (!HasAuthority())
					{
						// On Client
						Server_ThrowPowerBoomerang(BoomerangSpawnTransform);
					}
					else
					{
						// On Server
						// In order to set the movement direction of the projectile dynamically, we need to use this function
						currBoomerang = GetWorld()->SpawnActorDeferred<ABoomerang>(PowerBoomerangClass, BoomerangSpawnTransform);
						currBoomerang->Initialize(throwSpeed * 2.0f, currForwardDirection, this, true);

						// Once we are done, we then need to tell the object to finish spawning
						UGameplayStatics::FinishSpawningActor(currBoomerang, BoomerangSpawnTransform);
					}

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
}

// Checker to make sure that the server received the message properly
bool APlayerCharacter::Server_ThrowPowerBoomerang_Validate(FTransform boomerangSpawnTransform)
{
	return true;
}

// Server RPC to throw the power boomerang
void APlayerCharacter::Server_ThrowPowerBoomerang_Implementation(FTransform boomerangSpawnTransform)
{
	if (CheckIfActionable())
	{
		currBoomerang = GetWorld()->SpawnActorDeferred<ABoomerang>(PowerBoomerangClass, boomerangSpawnTransform);
		currBoomerang->Initialize(throwSpeed * 2.0f, currForwardDirection, this, true);
		UGameplayStatics::FinishSpawningActor(currBoomerang, boomerangSpawnTransform);
	}
}

// Influences the height of the thrown boomerang
// Note that we simply call a function in the boomerang to perform this action
void APlayerCharacter::ControlBoomerangHeight(float Value)
{
	if (!HasAuthority())
	{
		// On Client
		Server_ControlBoomerangHeight(Value);
	}
	else
	{
		// On Server
		if (CheckIfActionable())
		{
			if (currBoomerang != nullptr)
			{
				currBoomerang->ChangeHeight(Value);
			}
		}
	}
}

// Validation
bool APlayerCharacter::Server_ControlBoomerangHeight_Validate(float Value)
{
	return true;
}

// Server RPC that is called on client to run this on the server
void APlayerCharacter::Server_ControlBoomerangHeight_Implementation(float Value)
{
	if (CheckIfActionable())
	{
		if (currBoomerang != nullptr)
		{
			currBoomerang->ChangeHeight(Value);
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
	playerInputComponent->BindAxis("ChangeBoomerangHeight", this, &APlayerCharacter::ControlBoomerangHeight);

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

// Helper function used to remove the player from the game
// Note that only the server runs this
void APlayerCharacter::KillPlayer()
{
	if (CheckIfActionable() == true)
	{
		isAlive = false;
		
		this->SetActorHiddenInGame(true);
		this->SetActorEnableCollision(false);
		this->SetActorTickEnabled(false);
		
		// To respawn the player, we get the gamemode and we then call the respawn
		// Note that this only runs on the server
		// This will also take care of updating the HUD as well!
		ABrng_SourceGameMode* gm = Cast<ABrng_SourceGameMode>(GetWorld()->GetAuthGameMode());
		if (gm != nullptr)
		{
			gm->Respawn(GetController(), spawnLocation);
		}
	}
}

// Server RPC Validate
bool APlayerCharacter::Server_KillPlayer_Validate()
{
	return true;
}

// Server RPC to call this on all other clients
void APlayerCharacter::Server_KillPlayer_Implementation()
{
	if (CheckIfActionable() == true)
	{
		isAlive = false;

		this->SetActorHiddenInGame(true);
		this->SetActorEnableCollision(false);
		this->SetActorTickEnabled(false);
	}
}

// Damages the player. If the player health reaches 0, they die
void APlayerCharacter::DamagePlayer(float modder)
{
	if (CheckIfActionable())
	{
		if (!HasAuthority())
		{
			// On Client
			Server_DamagePlayer(modder);
		}
		else
		{
			// On Server
			currHealth = FMath::Clamp(currHealth - modder, 0.0f, maxHealth);
			if (currHealth <= 0.0f)
			{
				// Invoke death logic
				KillPlayer();
			}
		}
	}
}

// Validates logic in serer RPC
bool APlayerCharacter::Server_DamagePlayer_Validate(float modder)
{
	return true;
}

// Server RPC to update the server on the health
void APlayerCharacter::Server_DamagePlayer_Implementation(float modder)
{
	if (CheckIfActionable())
	{
		currHealth = FMath::Clamp(currHealth - modder, 0.0f, maxHealth);
		if (currHealth <= 0.0f)
		{
			// Invoke death logic
			Server_KillPlayer();
		}
	}
}

// Special Function to declare when we want to make specific parameters replicated
// Refer to https://docs.unrealengine.com/4.26/en-US/InteractiveExperiences/Networking/Actors/Properties/ for more details
void APlayerCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Specify all of the parameters that you want to replicate 
	DOREPLIFETIME(APlayerCharacter, currForwardDirection);
	DOREPLIFETIME(APlayerCharacter, isHolding);
	DOREPLIFETIME(APlayerCharacter, currTimeCharging);
	DOREPLIFETIME(APlayerCharacter, currTimeToRecharge);
	DOREPLIFETIME(APlayerCharacter, currHealth);
	DOREPLIFETIME(APlayerCharacter, maxHealth);
	DOREPLIFETIME(APlayerCharacter, isAlive);
	DOREPLIFETIME(APlayerCharacter, DisableMovement);
	DOREPLIFETIME(APlayerCharacter, spawnLocation);
	DOREPLIFETIME(APlayerCharacter, currBoomerang);
}