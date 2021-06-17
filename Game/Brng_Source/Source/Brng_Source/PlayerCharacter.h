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
#include "Blueprint/UserWidget.h" 
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Public/Net/UnrealNetwork.h"
#include "Math/BigInt.h" 
#include "PlayerCharacter.generated.h"

// Forward ddeclare these in the header
class ABoomerang;
class AMulti_Camera;
class UCustomPlayerHUD;

UCLASS()
class BRNG_SOURCE_API APlayerCharacter : public APaperCharacter
{
private:
	GENERATED_BODY()

	// Is the player holding down the shoot button?
	UPROPERTY(Replicated)
		bool isHolding;

	// How long has the player held down the button?
	UPROPERTY(Replicated)
		float currTimeCharging;

	// Current length of time during boomerang recharge
	UPROPERTY(Replicated)
		float currTimeToRecharge;

	// The current direction the player is facing
	// This needs to be replicated in order to make boomerang throwing work on client to server
	UPROPERTY(Replicated)
		int currForwardDirection;

	// Start Function; Runs at the start of the game
	virtual void BeginPlay() override;

	// The Update method; controls what this class does on each tick
	virtual void Tick(float DeltaSeconds) override;

	// Grabs the player input
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

	// Controls left/right movement
	void MoveHorizontal(float Value);

	// Turns the player left or right, depending on the current movement
	void TurnPlayer(float Value);

	// Shoot Boomerang
	void ThrowBoomerang();

	// Shoot a stronger boomerang
	void ThrowPowerBoomerang();

	// Checks if the player has enough energy to throw aa boomerang
	bool CheckIfEnoughEnergy(float cost);

	// Pointer to plyer camera
	AMulti_Camera* PlayerCam;
	
	// Pointer to current spawned Player UI Widget
	UCustomPlayerHUD* PlayerHUD;

protected:

	// To use UMG in codde, you need to add the module to the projectName.Build.cs file
	// https://nerivec.github.io/old-ue4-wiki/pages/umg-referencing-umg-widgets-in-code.html
	UPROPERTY(EditAnywhere, Category = "HUD")
		TSubclassOf<class UCustomPlayerHUD> PlayerHUDClass;

	// Ref to what camera blueprint to use
	UPROPERTY(EditAnywhere, Category = "Camera")
		TSubclassOf<class AMulti_Camera> PlayerCamClass;

	// Position of the camera that will be set on start
	UPROPERTY(EditAnywhere, Category = "Camera")
		FVector PlayerCameraPosition;

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

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Health")
		float currHealth;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Health")
		float maxHealth;

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

	// This is a little tricky, so to make a server RPC, we need to know what function we want to use and make sure
	// That function has the following methods with the EXACT names as shown here
	// Server (prefix) and _Validate / _Implementation
	// we do NOT need to implement the top method; this is already done on UE side
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ThrowBoomerang(FTransform boomerangSpawnTransform);
	bool Server_ThrowBoomerang_Validate(FTransform boomerangSpawnTransform);
	void Server_ThrowBoomerang_Implementation(FTransform boomerangSpawnTransform);

	// Server RPC to make sure that the power boomerang works
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ThrowPowerBoomerang(FTransform boomerangSpawnTransform);
	bool Server_ThrowPowerBoomerang_Validate(FTransform boomerangSpawnTransform);
	void Server_ThrowPowerBoomerang_Implementation(FTransform boomerangSpawnTransform);

	// Server RPC for player turning, required for making boomerang throws accurate
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_TurnPlayer(float MoveDir);
	bool Server_TurnPlayer_Validate(float MoveDir);
	void Server_TurnPlayer_Implementation(float MoveDir);

public:

	// Constructor for this class; sets defaults
	APlayerCharacter();

	// Called to invoke damage on the player
	void DamagePlayer(float modder);

	// Server RPC to update player health
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_DamagePlayer(float modder);
	bool Server_DamagePlayer_Validate(float modder);
	void Server_DamagePlayer_Implementation(float modder);
};
