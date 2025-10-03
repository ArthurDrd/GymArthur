// // Copyright (c) 2025, Arthur Durand. All rights reserved.


#include "AI/Traits/GAMovementTrait.h"
#include "MassEntityTemplateRegistry.h"
#include "AI/Fragments/GAFragments.h"

void UGAMovementTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddFragment<FGATargetFragment>();
}
