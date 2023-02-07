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

	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;

	DrawDebugLine(GetWorld(), Start, End, FColor::Cyan);
	
	const float Demage = 10;
	PrintDemage(Demage);

	//References
	/*float Demage = 10;
	float& DemageRef = Demage;
	DemageRef = 5;
	UE_LOG(LogTemp, Display, TEXT("Demage: %f DemageRef: %f"), Demage, DemageRef);*/

	
	/*FRotator CurrentRotation = GetComponentRotation();
	FString RotationString = CurrentRotation.ToCompactString();

	UE_LOG(LogTemp, Display, TEXT("Rotation is ticking: %s"), *RotationString);

	UWorld* World = GetWorld();
	float WorldTime = World->TimeSeconds;
	UE_LOG(LogTemp, Display, TEXT("World time: %f"), WorldTime);
	*/

}

void UGrabber::PrintDemage(const float& Demage)
{
	
	UE_LOG(LogTemp, Display, TEXT("Demage: %f "), Demage); 

}
