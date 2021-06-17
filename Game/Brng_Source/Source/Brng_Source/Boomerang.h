// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/Engine/Public/Net/UnrealNetwork.h"
#include "Boomerang.generated.h"

UCLASS()
class BRNG_SOURCE_API ABoomerang : public AActor
{
	GENERATED_BODY()

private:

	// Used to keep track of the time elapsed since it was created.
	float timeElapsed;

	// Keeps a ref to the original initial move dir that was passed in
	float initialMoveDir;

	// A ref to the lerpedX value that was gotten
	float lerpedX;

	// Has the boomerang reversed directions?
	bool hasReversed;

	// The original thrower of the object
	UPROPERTY(Replicated)
		AActor* originalThrower;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Pointer to the visual part of the boomerang
	UPROPERTY(EditAnywhere, Category = "Components")
		UPaperSpriteComponent* BoomerangSprite;

	// Movement logic pointer
	UPROPERTY(EditAnywhere, Category = "Components")
		UProjectileMovementComponent* BoomerangMovement;

	// How long does it take for the boomerang to reverse direction
	UPROPERTY(EditAnywhere, Category = "Movement")
		float timeToReverse;

	// This handles how fast the boomerang reaches its top speed
	UPROPERTY(EditAnywhere, Category = "Movement", meta = (ClampMin = "0.01", ClampMax = "1.0"))
		float boomerangAcceleration;

	// Is this boomerang a powerful one?
	UPROPERTY(Replicated, EditAnywhere, Category = "Fight")
		bool isPowerBoomerang;

	// Base power of a standard thhrow
	UPROPERTY(EditAnywhere, Category = "Fight")
		float normalPower;

	// Base power of a power throw
	UPROPERTY(EditAnywhere, Category = "Fight")
		float increasedPower;

	// Delegate function that handles actor collisions
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Sets default values for this actor's properties
	ABoomerang();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Prepares the object's variables
	void Initialize(float moveSpeed, int moveDir, AActor* originOwner, bool isPower);

};
