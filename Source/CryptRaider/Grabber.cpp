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
	UE_LOG(LogTemp, Display, TEXT("Release"));
}

void UGrabber::Grab()
{

	
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;

	DrawDebugLine(GetWorld(), Start, End, FColor::Cyan);

	FHitResult HitResult;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start,
		End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	);

	if (HasHit)
	{
		AActor* Test = HitResult.GetActor();

		UE_LOG(LogTemp, Display, TEXT("Hit name: %s"), *Test->GetActorNameOrLabel());
	}
}


