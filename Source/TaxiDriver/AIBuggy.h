// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "RoadActor.h"
#include "Components/SceneComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AIBuggy.generated.h"

/**
 * 
 */
UCLASS()
class TAXIDRIVER_API AAIBuggy : public AWheeledVehiclePawn
{
    GENERATED_BODY()

public:
    // Constructor
    AAIBuggy();

    // Called on game start
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // We won't use this since it's AI
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    // Instance of Spline to be followed
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline", meta = (AllowPrivateAccess = "true"))
        ARoadActor* SplineToFollow;

    // two sensors at front of car
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<USceneComponent> RP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TObjectPtr<USceneComponent> LP;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* LPSpringArm;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
    USpringArmComponent* RPSpringArm;

    float TargetSplineDistance{0.0f};
    float CheckGap{500.0f};

    void SetSteering();

    void SetSpeed(float Mph);

private:
    // Implement any additional functions or variables as needed
    // For example, your accelerate function:
    void Accelerate(float Throttle);

    void Brake(float Brake);

    void Turn(float Direction);
	
};
