// // Copyright (c) 2025, Arthur Durand. All rights reserved.

#include "GASimpleRandomMovementTrait.h"
#include "MassEntityTemplateRegistry.h"

void UGASimpleRandomMovementTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext,
	const UWorld& World) const
{
	BuildContext.AddFragment<FGATargetFragment>();
}
