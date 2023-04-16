// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

// Sets default values for this component's properties
UTriggerComponent::UTriggerComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* actor = GetAcceptableActor();

    if(actor)
    {
        mover->SetShouldMove(true);
    }
    else
    {
        mover->SetShouldMove(false);
    }
}

void UTriggerComponent::SetMover(UMover* newMover) 
{
    mover = newMover;
}

AActor* UTriggerComponent::GetAcceptableActor() const 
{
    TArray<AActor*> actors;

    GetOverlappingActors(actors);

    for (AActor* actor : actors)
    {
        if(actor->ActorHasTag(acceptableActorTag))
        {
            return actor;
        }
    }

    return nullptr;
}
