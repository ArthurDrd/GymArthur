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

	CachedCharacter = Cast<AGACharacterBase>(GetCharacter());
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
	if (!CachedCharacter) return;
	
	const FVector2d MoveVector = InputActionValue.Get<FVector2d>();
	if (MoveVector.SquaredLength() == 0) return;
	
	const FRotator YawRotation(0.0f, GetControlRotation().Yaw, 0.0f);

	const FVector ForwardDirection(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
	const FVector RightDirection(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
	
	CachedCharacter->AddMovementInput(ForwardDirection, MoveVector.Y);
	CachedCharacter->AddMovementInput(RightDirection, -MoveVector.X);
}

void AGAPlayerControllerBase::InputZoom(const FInputActionValue& InputActionValue)
{
	if (!CachedCharacter) return;
	
	CachedCharacter->ChangeArmLenght(1000.f * InputActionValue.Get<float>());
}

void AGAPlayerControllerBase::InputSprint(const FInputActionValue& InputActionValue)
{
	if (!CachedCharacter) return;
	
	if (InputActionValue.Get<bool>())
	{
		bIsSprinting = true;
		CachedCharacter->GetCharacterMovement()->MaxWalkSpeed = 800.f;
	}
	else
	{
		bIsSprinting = false;
		CachedCharacter->GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}
}
