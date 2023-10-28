// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBuggy.h"
#include "ChaosWheeledVehicleMovementComponent.h"

AAIBuggy::AAIBuggy()
{
	CheckGap = 1000.0f;
	PrimaryActorTick.bCanEverTick = true;
	SplineToFollow = nullptr;

	// SpringArm Setup for sensors
	RPSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("RPSpringArm"));
	RPSpringArm->SetupAttachment(RootComponent); 
	RPSpringArm->SetRelativeLocation(FVector(260, 90, 0));

	LPSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("LPSpringArm"));
	LPSpringArm->SetupAttachment(RootComponent);
	LPSpringArm->SetRelativeLocation(FVector(260, -90, 0));

	// Sensors attached to SpringArms
	RP = CreateDefaultSubobject<USceneComponent>(TEXT("RP"));
	RP->SetupAttachment(RPSpringArm);
	RP->SetRelativeLocation(FVector(300, 0, 0));

	LP = CreateDefaultSubobject<USceneComponent>(TEXT("LP"));
	LP->SetupAttachment(LPSpringArm);
	LP->SetRelativeLocation(FVector(300, 0, 0));
	
}

void AAIBuggy::BeginPlay()
{
	Super::BeginPlay();
}

void AAIBuggy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

	// Accelerate constantly, maxing out at a speed of 30
	SetSpeed(20.0f);


	// Steering Logic
	SetSteering();

}

// We won't use this since it's AI
void AAIBuggy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAIBuggy::SetSteering()
{
	if (SplineToFollow != nullptr && SplineToFollow->SplineComponent != nullptr)
	{
		// Restart loop once full circle completed
		if (TargetSplineDistance > SplineToFollow->SplineComponent->GetSplineLength())
		{
			TargetSplineDistance = 0;
		}

		// Steering Logic

		// set TargetPoint to world coordinate along length of spline
		FVector TargetPoint = SplineToFollow->SplineComponent->GetLocationAtDistanceAlongSpline(TargetSplineDistance, ESplineCoordinateSpace::World);

		// if vehicle is close enough to target point, increment target point
		double Distance = FVector::Distance(TargetPoint, GetActorLocation());

		if (Distance < CheckGap)
		{
			TargetSplineDistance += CheckGap;
		}

		// calculate distance of each sensor from target point
		double LSenseDist = FVector::Distance(TargetPoint, LP->K2_GetComponentLocation());
		double RSenseDist = FVector::Distance(TargetPoint, RP->K2_GetComponentLocation());

		// steer based on sensor distance
		if (abs(LSenseDist - RSenseDist) < 5.0f) {
			Turn(0.0f);
		}
		else if (LSenseDist > RSenseDist)
		{
			Turn(0.5f);
		}
		else
		{
			Turn(-0.5f);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Bruh Where's the Spline?"));
	}

}

void AAIBuggy::SetSpeed(float Mph)
{
	// Check for component
	if (GetVehicleMovementComponent())
	{
		// Accelerate to specified speed
		if (GetVehicleMovementComponent()->GetForwardSpeedMPH() <= Mph)
		{
			Accelerate(1.0);
		}
		// While above but close to speed, don't accelerate
		else if (GetVehicleMovementComponent()->GetForwardSpeedMPH() <= Mph + 3)
		{
			Accelerate(0.0);
		}
		// While far above speed, brake
		else
		{
			Brake(1.0);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Chaos Wheeled Vehicle Movement Component not found on the spawned vehicle!"));
	}
}

void AAIBuggy::Accelerate(float Throttle)
{
	// Set throttle input to accelerate the vehicle
	GetVehicleMovementComponent()->SetThrottleInput(Throttle);
	GetVehicleMovementComponent()->SetBrakeInput(0.0f);
}

void AAIBuggy::Brake(float Brake)
{
	// Set brake input to stop the vehicle
	GetVehicleMovementComponent()->SetThrottleInput(0.0f);
	GetVehicleMovementComponent()->SetBrakeInput(Brake);
}

void AAIBuggy::Turn(float Direction)
{
	if (GetVehicleMovementComponent())
	{
		GetVehicleMovementComponent()->SetSteeringInput(Direction);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Chaos Wheeled Vehicle Movement Component not found on the spawned vehicle!"));
	}
}
