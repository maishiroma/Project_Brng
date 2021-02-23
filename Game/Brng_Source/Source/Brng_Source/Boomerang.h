// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
		UPaperSpriteComponent* BoomerangSprite;

	UPROPERTY(EditAnywhere, Category = "Components")
		UProjectileMovementComponent* BoomerangMovement;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float timeToReverse;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
		bool hasSwitched;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Sets default values for this actor's properties
	ABoomerang();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Prepares the object's variables
	void Initialize(float moveSpeed, int moveDir);

};
