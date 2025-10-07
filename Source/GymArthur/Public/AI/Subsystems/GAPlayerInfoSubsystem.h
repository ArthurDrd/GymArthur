// // Copyright (c) 2025, Arthur Durand. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MassSubsystemBase.h"
#include "MassProcessor.h"
#include "GAPlayerInfoSubsystem.generated.h"

UCLASS()
class GYMARTHUR_API UGAPlayerInfoSubsystem : public UMassTickableSubsystemBase
{
	GENERATED_BODY()

public:
	FVector GetPlayerLocation() const;

protected:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
	
private:
	FVector PlayerLocation;

	UPROPERTY()
	APawn* CachedPlayerPawn;
	
};
