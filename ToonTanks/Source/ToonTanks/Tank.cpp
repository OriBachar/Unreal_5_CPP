// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    springArmComponent->SetupAttachment(RootComponent);

    cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    cameraComponent->SetupAttachment(springArmComponent);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!tankPlayerController) return;

    FHitResult hitResult;

    tankPlayerController->GetHitResultUnderCursor(
        ECollisionChannel::ECC_Visibility, 
        false,
        hitResult
    );

    RotateTurret(hitResult.ImpactPoint);
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
    tankPlayerController = Cast<APlayerController>(GetController());
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

    playerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);

    playerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

    playerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}


void ATank::Move(float value)
{
    FVector deltaLocation = FVector::ZeroVector;

    deltaLocation.X = value * speed * UGameplayStatics::GetWorldDeltaSeconds(this);

    AddActorLocalOffset(deltaLocation, true);
}

void ATank::Turn(float value)
{
    FRotator deltaRotation = FRotator::ZeroRotator;

    deltaRotation.Yaw = value * turnRate * UGameplayStatics::GetWorldDeltaSeconds(this);

    AddActorLocalRotation(deltaRotation, true);
}

void ATank::HandleDestruction() 
{
    Super::HandleDestruction();

    SetActorHiddenInGame(true);

    SetActorTickEnabled(false);
}