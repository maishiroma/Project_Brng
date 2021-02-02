// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Boomerang.generated.h"

UCLASS()
class BRNG_SOURCE_API ABoomerang : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoomerang();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
		UPaperSpriteComponent* BoomerangSprite;

	UPROPERTY(EditAnywhere, Category = "Components")
		class UProjectileMovementComponent* BoomerangMovement;

	UFUNCTION()
	void OnTriggerEnter(AActor* OverlappedActor, AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Prepares the object's variables
	void Initialize(float moveSpeed, int moveDir);

};
