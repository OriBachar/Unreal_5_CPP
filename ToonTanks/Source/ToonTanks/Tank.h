// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* springArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* cameraComponent;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float speed = 800.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float turnRate = 120.f;

	APlayerController* playerControllerRef;

	void Move(float value);

	void Turn(float value);
	
};
