// // Copyright (c) 2025, Arthur Durand. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "MassEntityTraitBase.h"
#include "GATargetingTrait.generated.h"

UCLASS()
class GYMARTHUR_API UGATargetingTrait : public UMassEntityTraitBase
{
	GENERATED_BODY()

protected:
	virtual void BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const override;
};
