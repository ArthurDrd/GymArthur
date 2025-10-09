// // Copyright (c) 2025, Arthur Durand. All rights reserved.


#include "Characters/GACharacterBase.h"

AGACharacterBase::AGACharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	// Spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetMesh(),FName("SOCKET_Camera"));

	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void AGACharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AGACharacterBase::ChangeArmLenght(const float Value)
{
	const float NewLenght = FMath::Clamp(SpringArm->TargetArmLength + Value, 1000, 5000.f);
	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, NewLenght, GetWorld()->GetDeltaSeconds(), 20.f);
}