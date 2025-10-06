// // Copyright (c) 2025, Arthur Durand. All rights reserved.


#include "Controllers/PlayerControllers/GAPlayerControllerBase.h"

#include "EnhancedInputSubsystems.h"
#include "Characters/GACharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTags/GAGameplayTags.h"
#include "Inputs/GATaggedInputComponent.h"

AGAPlayerControllerBase::AGAPlayerControllerBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGAPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	// Set the mapping context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// Subsystem is valid : this is the local player
		Subsystem->AddMappingContext(IMC, 0);
	}
}

void AGAPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Check if we are using the right InputComponent
	auto* TaggedInputComponent = CastChecked<UGATaggedInputComponent>(InputComponent);

	// Bind the actions
	TaggedInputComponent->BindActionByTag(InputConfig, TAG_Input_Move, ETriggerEvent::Triggered, this, &AGAPlayerControllerBase::InputMove);
	TaggedInputComponent->BindActionByTag(InputConfig, TAG_Input_Zoom, ETriggerEvent::Triggered, this, &AGAPlayerControllerBase::InputZoom);
	TaggedInputComponent->BindActionByTag(InputConfig, TAG_Input_Sprint, ETriggerEvent::Triggered, this, &AGAPlayerControllerBase::InputSprint);
}

void AGAPlayerControllerBase::InputMove(const FInputActionValue& InputActionValue)
{
	const FVector2d MoveVector = InputActionValue.Get<FVector2d>();
	if (MoveVector.SquaredLength() == 0) return;
	
	const FRotator YawRotation(0.0f, GetControlRotation().Yaw, 0.0f);

	const FVector ForwardDirection(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
	const FVector RightDirection(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, MoveVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, -MoveVector.X);
	}
}

void AGAPlayerControllerBase::InputZoom(const FInputActionValue& InputActionValue)
{
	// Empty for now
}

void AGAPlayerControllerBase::InputSprint(const FInputActionValue& InputActionValue)
{
	AGACharacterBase* ControlledCharacter = Cast<AGACharacterBase>(GetCharacter());

	if (!ControlledCharacter) return;
	
	if (InputActionValue.Get<bool>())
	{
		bIsSprinting = true;
		ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = 800.f;
	}
	else
	{
		bIsSprinting = false;
		ControlledCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}
}
