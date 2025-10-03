// // Copyright (c) 2025, Arthur Durand. All rights reserved.


#include "AI/Traits/GATargetingTrait.h"
#include "MassEntityTemplateRegistry.h"
#include "AI/Fragments/GAFragments.h"

void UGATargetingTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.AddFragment<FGATargetFragment>();
}
