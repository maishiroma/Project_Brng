// Fill out your copyright notice in the Description page of Project Settings.


#include "Boomerang.h"
#include "PlayerCharacter.h"

// Sets default values
ABoomerang::ABoomerang()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates the object's componenets
	BoomerangSprite = CreateDefaultSubobject<UPaperSpriteComponent>("BoomerangSprite");
	BoomerangMovement = CreateDefaultSubobject<UProjectileMovementComponent>("BoomerangMovement");

	// Defaults for Blueprints
	BoomerangMovement->ProjectileGravityScale = 0.0f;

	// Private Variables
	normalPower = 10.0f;
	increasedPower = 50.0f;
	isPowerBoomerang = false;
	timeElapsed = 0.0f;
	initialMoveDir = 1.0f;
	lerpedX = 0.0f;
	hasReversed = false;

	SetRootComponent(BoomerangSprite);
}

// Called when the game starts or when spawned
void ABoomerang::BeginPlay()
{
	Super::BeginPlay();

	// Sprite Components handle their own collison, no need to specify a box collider
	// Also, this particular delegation should be done in BeginPlay not in the constructor
	// https://forums.unrealengine.com/development-discussion/c-gameplay-programming/106815-how-to-use-onactorbeginoverlap-c-code
	BoomerangSprite->OnComponentBeginOverlap.AddDynamic(this, &ABoomerang::OnOverlapBegin);
	
}

// Called every frame
void ABoomerang::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Since this is a boomerang, it should return back in the opposite direction it was thrown
	if (timeElapsed > timeToReverse)
	{
		if (hasReversed == false)
		{
			// Once we initiated the reverse movement, we set the lerp to be the opposite of the moveDir
			// This is done so the movement backwards is faster + less stalling
			lerpedX = -initialMoveDir;
			hasReversed = true;
		}
		
		// We lerp between the current direction and the inverse direction
		lerpedX = FMath::Lerp(lerpedX, -initialMoveDir, boomerangAcceleration);
		
		// To make the boomerang go faster gradually, we use add force to gradually speed up the boomerang
		BoomerangMovement->AddForce(FVector(lerpedX * BoomerangMovement->InitialSpeed, 0.0f, 0.0f));
	}
	else
	{
		// We lerp between the current direction and the inverse direction
		lerpedX = FMath::Lerp(lerpedX, -initialMoveDir, boomerangAcceleration);
		
		// To preserve the speed of the boomerang, we need to times our lerped value back to the initial speed of the boomerang
		BoomerangMovement->SetVelocityInLocalSpace(FVector(lerpedX * BoomerangMovement->InitialSpeed, 0.0f, 0.0f));

		timeElapsed += DeltaTime;
	}
}

// Initializes the boomerange's properties
void ABoomerang::Initialize(float moveSpeed, int moveDir, AActor* originOwner, bool isPower)
{
	if (BoomerangMovement != nullptr)
	{
		// Sets up the movement component
		BoomerangMovement->InitialSpeed = moveSpeed;
		BoomerangMovement->MaxSpeed = moveSpeed * 10.0f;
		BoomerangMovement->SetVelocityInLocalSpace(FVector(moveDir, 0.0f, 0.0f));

		// Sets up private variables
		initialMoveDir = moveDir;
		isPowerBoomerang = isPower;

		// We do an initial calculation here so that we can lerp on the new value afterwards
		lerpedX = FMath::Lerp(initialMoveDir, initialMoveDir * -1.0f, 0.01f);

		// Set the original owner who threw this
		originalThrower = originOwner;
	}
}

// Delegated function that is called when this boomerang overlaps another actor
void ABoomerang::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Easiest is to use tag checking, like in Unity
	if (OtherComp->GetOwner()->ActorHasTag("Player") == true && originalThrower != nullptr)
	{
		// We hit another player
		if (OtherComp->GetOwner()->GetName() != originalThrower->GetName())
		{
			// We get the playerCharacter component and take away health
			APlayerCharacter* test = Cast<APlayerCharacter>(OtherComp->GetOwner());
			if (!isPowerBoomerang)
			{
				test->DamagePlayer(normalPower);
			}
			else
			{
				test->DamagePlayer(increasedPower);
			}
		}
	}
	
	// On all collisions, it will destroy itself when it hits anything
	Destroy();
}

// Used to mark specific attributes as replicated
void ABoomerang::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Specify all of the parameters that you want to replicate 
	DOREPLIFETIME(ABoomerang, originalThrower);
	DOREPLIFETIME(ABoomerang, isPowerBoomerang);
}