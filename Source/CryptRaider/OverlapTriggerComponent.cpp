// Fill out your copyright notice in the Description page of Project Settings.


#include "OverlapTriggerComponent.h"

void UOverlapTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("Trigger component alive"));


}