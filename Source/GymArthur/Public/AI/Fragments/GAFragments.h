// // Copyright (c) 2025, Arthur Durand. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTypes.h"
#include "GAFragments.generated.h"

USTRUCT(BlueprintType)
struct GYMARTHUR_API FGATargetFragment  : public FMassFragment
{
	GENERATED_BODY()
	
	FVector Target = FVector::ZeroVector;
};