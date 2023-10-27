// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "AIBuggy.generated.h"

/**
 * 
 */
UCLASS()
class TAXIDRIVER_API AAIBuggy : public AWheeledVehiclePawn
{
public:
    // Constructor
    AAIBuggy();

    // Called on game start
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // We won't use this since it's AI
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Implement any additional functions or variables as needed
    // For example, your accelerate function:
    UFUNCTION(BlueprintCallable, Category = "ChaosVehicle")
	    void Accelerate();

private:

	GENERATED_BODY()
	
};
