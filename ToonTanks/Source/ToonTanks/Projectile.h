// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent* projectileMesh;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* projectileMovementComponent;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* hitComp, 
		AActor* otherActor, 
		UPrimitiveComponent* otherComp, 
		FVector normalImpulse, 
		const FHitResult& hit
	);

	UPROPERTY(EditAnywhere, Category = "Combat")
	float damage = 50.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
