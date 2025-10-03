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
