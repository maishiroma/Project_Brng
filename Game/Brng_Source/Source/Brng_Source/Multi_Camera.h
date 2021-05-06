// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h" 
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Multi_Camera.generated.h"

UCLASS()
class BRNG_SOURCE_API AMulti_Camera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMulti_Camera();

protected:
	// Creates a static mesh to help debug the camera position
	UPROPERTY(EditAnywhere, Category = "Components")
		UPaperSpriteComponent* DebugVisual;

	UPROPERTY(EditAnywhere, Category = "Components")
		USpringArmComponent* CamArm;

	UPROPERTY(EditAnywhere, Category = "Components")
		UCameraComponent* CameraComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
