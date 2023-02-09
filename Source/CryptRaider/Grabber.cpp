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

	UPhysicsHandleComponent* PhysicsHandler = getHandleComponent();
	if (PhysicsHandler == nullptr)
	{
		return;
	}

	

	if (PhysicsHandler->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandler->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
	/*FRotator CurrentRotation = GetComponentRotation();
	FString RotationString = CurrentRotation.ToCompactString();

	UE_LOG(LogTemp, Display, TEXT("Rotation is ticking: %s"), *RotationString);

	UWorld* World = GetWorld();
	float WorldTime = World->TimeSeconds;
	UE_LOG(LogTemp, Display, TEXT("World time: %f"), WorldTime);
	*/

}

void UGrabber::Release()
{
	
		UPhysicsHandleComponent* PhysicsHandler = getHandleComponent();

		if (PhysicsHandler == nullptr)
		{
			return;
		}

		FHitResult HitResult;
		if (PhysicsHandler->GetGrabbedComponent() != nullptr) 
		{
			PhysicsHandler->ReleaseComponent();
		}
		else
		{
			return;
		}

}
bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;

	DrawDebugLine(GetWorld(), Start, End, FColor::Cyan);
	DrawDebugSphere(GetWorld(), End, 10, 10, FColor::Blue, false, 3);
	

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);

}
void UGrabber::Grab()
{
	
	UPhysicsHandleComponent* PhysicsHandler = getHandleComponent();
	if (PhysicsHandler == nullptr)
	{
		return;
	}
	
	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult);

	if (HasHit)
		{	
		//waking up all bodies
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();

		DrawDebugSphere(GetWorld(), HitResult.Location, 10, 10, FColor::Green, false, 3);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Red, false, 3);

		PhysicsHandler->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}

UPhysicsHandleComponent* UGrabber::getHandleComponent() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr) 
	{
		UE_LOG(LogTemp, Error, TEXT("UPhysicsHandleComponent is null"));

	}
	 return Result;
}



