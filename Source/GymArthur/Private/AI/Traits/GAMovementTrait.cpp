// // Copyright (c) 2025, Arthur Durand. All rights reserved.


#include "AI/Traits/GAMovementTrait.h"
#include "MassEntityTemplateRegistry.h"
#include "MassCommonFragments.h" 
#include "MassNavigationFragments.h"

void UGAMovementTrait::BuildTemplate(FMassEntityTemplateBuildContext& BuildContext, const UWorld& World) const
{
	BuildContext.RequireFragment<FTransformFragment>();
	BuildContext.RequireFragment<FMassMoveTargetFragment>();
}
