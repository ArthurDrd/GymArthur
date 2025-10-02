// // Copyright (c) 2025, Arthur Durand. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityElementTypes.h"
#include "MassEntityTraitBase.h"
#include "GASimpleRandomMovementTrait.generated.h"

USTRUCT()
struct FGATargetFragment  : public FMassFragment
{
	GENERATED_BODY()
	FVector Target;
};

UCLASS()
class UGASimpleRandomMovementTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};