// Fill out your copyright notice in the Description page of Project Settings.


#include "Multi_Camera.h"

// Sets default values
AMulti_Camera::AMulti_Camera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DebugVisual = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Debug Visual"));
	DebugVisual->SetCollisionProfileName("NoCollision");
	SetRootComponent(DebugVisual);

	CamArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));

	// https://answers.unrealengine.com/questions/665668/c-attachtocomponent-syntax.html
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->AttachToComponent(CamArm, FAttachmentTransformRules::KeepWorldTransform);
}

// Called when the game starts or when spawned
void AMulti_Camera::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMulti_Camera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

