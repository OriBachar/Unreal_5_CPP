// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();

	if(physicsHandle && physicsHandle->GetGrabbedComponent()) 
	{
		FVector targetLocation = GetComponentLocation() + GetForwardVector() * holdDistance;

		physicsHandle->SetTargetLocationAndRotation(targetLocation, GetComponentRotation());
	}

}

void UGrabber::Grab()
{

	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();

	if(!physicsHandle)
	{
		return;
	}

	FHitResult hitResult;

	bool hasHit = GetGrabbableInReach(hitResult);

	if(hasHit)
	{
		UPrimitiveComponent* hitComponent = hitResult.GetComponent();

		hitComponent->SetSimulatePhysics(true); 

		hitComponent->WakeAllRigidBodies();

		hitResult.GetActor()->Tags.Add("Grabbed");

		hitResult.GetActor()->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		physicsHandle->GrabComponentAtLocationWithRotation(
			hitComponent,
			NAME_None,
			hitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
	
}

void UGrabber::Release()
{
	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();

	if(physicsHandle && physicsHandle->GetGrabbedComponent())
	{
		physicsHandle->GetGrabbedComponent()->WakeAllRigidBodies();

		physicsHandle->GetGrabbedComponent()->GetOwner()->Tags.Remove("Grabbed");

		physicsHandle->ReleaseComponent();
	}


}

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if(!result)
	{
		UE_LOG(LogTemp, Error, TEXT("Grabber requires a UPhysicsHandleComponent"));
	}

	return result;

}

bool UGrabber::GetGrabbableInReach(FHitResult& outHitResult) const 
{
	FVector start = GetComponentLocation();

	FVector end = start + GetForwardVector() * maxGrabDistance;

	DrawDebugLine(GetWorld(), start, end, FColor::Blue);

	FCollisionShape sphere = FCollisionShape::MakeSphere(grabRadius);

	return GetWorld()->SweepSingleByChannel(
		outHitResult, 
		start, 
		end, 
		FQuat::Identity, 
		ECC_GameTraceChannel2,
		sphere
	);
}
