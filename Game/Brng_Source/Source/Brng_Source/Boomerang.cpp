// Fill out your copyright notice in the Description page of Project Settings.


#include "Boomerang.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABoomerang::ABoomerang()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates the object's componenets
	BoomerangSprite = CreateDefaultSubobject<UPaperSpriteComponent>("BoomerangSprite");
	BoomerangMovement = CreateDefaultSubobject<UProjectileMovementComponent>("BoomerangMovement");

	SetRootComponent(BoomerangSprite);
	
	// Need to make a delegate to perform collision (doesn't work)
	OnActorBeginOverlap.AddDynamic(this, &ABoomerang::OnTriggerEnter);
}

// Called when the game starts or when spawned
void ABoomerang::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoomerang::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Initializes the boomerange's properties
void ABoomerang::Initialize(float moveSpeed, int moveDir)
{
	if (BoomerangMovement != nullptr)
	{
		BoomerangMovement->InitialSpeed = moveSpeed;
		BoomerangMovement->MaxSpeed = moveSpeed;

		BoomerangMovement->SetVelocityInLocalSpace(FVector(moveDir, 0.0f, 0.0f));
	}
}

// Delegated function that is called when this boomerang hits another actor
void ABoomerang::OnTriggerEnter(AActor* OverlappedActor, AActor* OtherActor)
{
	// We destroy this boomerang
	Destroy();
}