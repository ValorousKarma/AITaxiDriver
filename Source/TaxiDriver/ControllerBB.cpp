// Fill out your copyright notice in the Description page of Project Settings.


#include "ControllerBB.h"
#include "CharacterBB.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


void AControllerBBBase::HandleLook(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void AControllerBBBase::HandleMove(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector(), MovementVector.Y);
	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector(), MovementVector.X);
}

void AControllerBBBase::HandleJump()
{
	PlayerCharacter->UnCrouch();
	PlayerCharacter->Jump();
}

void AControllerBBBase::HandleCrouch()
{
	if (PlayerCharacter->CanCrouch())
	{
		PlayerCharacter->Crouch();
	}
	else
	{
		PlayerCharacter->UnCrouch();
	}
}

void AControllerBBBase::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	// Store a reference to the Player's Pawn
	PlayerCharacter = Cast<ACharacterBB>(aPawn);
	checkf(PlayerCharacter, TEXT("AControllerBBBase derived classes should only posess ACharacterBBBase"));

	// Get a referenced to EnhancedInputComponent.
	EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(PlayerCharacter, TEXT("Unable to get reference to the EnhancedInputComponent"));

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	checkf(InputSubsystem, TEXT("Unable to get reference to EnhancedInputLocalPlayerSubsystem."));

	// Wipe existing mappings, add ours
	checkf(InputMappingContext, TEXT("InputMappingContext was not specified."));
	InputSubsystem->ClearAllMappings();
	InputSubsystem->AddMappingContext(InputMappingContext, 0);


	// Bind the input actions
	// Only attempt to bind if a valid value was provided.
	if (ActionMove)
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, 
			&AControllerBBBase::HandleMove);
	if (ActionLook)
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this,
			&AControllerBBBase::HandleLook);
	if (ActionJump)
		EnhancedInputComponent->BindAction(ActionJump, ETriggerEvent::Triggered, this,
			&AControllerBBBase::HandleJump);
	if (ActionCrouch)
		EnhancedInputComponent->BindAction(ActionCrouch, ETriggerEvent::Triggered, this,
			&AControllerBBBase::HandleCrouch);
}

void AControllerBBBase::OnUnPossess()
{
	EnhancedInputComponent->ClearActionBindings();

	Super::OnUnPossess();
}
