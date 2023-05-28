// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"


void ATower::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    if(!tank)
    {
        return;
    }

    float distance = FVector::Dist(GetActorLocation(), tank->GetActorLocation());

    if(distance <= fireRange)
    {
        RotateTurret(tank->GetActorLocation());
    }


}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	
    tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}
