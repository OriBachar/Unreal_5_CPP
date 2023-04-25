// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"



ATank::ATank()
{
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    springArmComponent->SetupAttachment(RootComponent);

    cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    cameraComponent->SetupAttachment(springArmComponent);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);

    playerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);

}


void ATank::Move(float value)
{

}




