// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBuggy.h"
#include "ChaosWheeledVehicleMovementComponent.h"

AAIBuggy::AAIBuggy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAIBuggy::BeginPlay()
{
	Super::BeginPlay();

	Accelerate();
}

void AAIBuggy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// We won't use this since it's AI
void AAIBuggy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AAIBuggy::Accelerate()
{
	if (GetVehicleMovementComponent())
	{
		// Set throttle input to accelerate the vehicle
		GetVehicleMovementComponent()->IncreaseThrottleInput(1.0f); // 1.0f represents full throttle, adjust as needed
		UE_LOG(LogTemp, Warning, TEXT("Throttle Set!"));
	}
	else
	{
			UE_LOG(LogTemp, Warning, TEXT("Chaos Wheeled Vehicle Movement Component not found on the spawned vehicle!"));
	}
}