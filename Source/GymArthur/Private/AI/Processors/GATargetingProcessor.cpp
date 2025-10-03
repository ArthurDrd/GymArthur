// // Copyright (c) 2025, Arthur Durand. All rights reserved.


#include "AI/Processors/GATargetingProcessor.h"

#include "MassCommonFragments.h"
#include "MassCommonTypes.h"
#include "MassExecutionContext.h"
#include "AI/Fragments/GAFragments.h"

UGATargetingProcessor::UGATargetingProcessor() : EntityQuery(*this)
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = (int32)(EProcessorExecutionFlags::All);
	ExecutionOrder.ExecuteBefore.Add(UE::Mass::ProcessorGroupNames::Avoidance);
}

void UGATargetingProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadOnly);
	EntityQuery.AddRequirement<FGATargetFragment>(EMassFragmentAccess::ReadWrite);
}

void UGATargetingProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk( Context, [this](FMassExecutionContext& Context)
	{
		const TArrayView<const FTransformFragment> TransformsList = Context.GetFragmentView<FTransformFragment>();
		const TArrayView<FGATargetFragment> SimpleMovementsList =
			Context.GetMutableFragmentView<FGATargetFragment>();
		
		
		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		{
			const FTransform& Transform = TransformsList[EntityIndex].GetTransform();
			FVector& MoveTarget = SimpleMovementsList[EntityIndex].Target;
			
			FVector CurrentLocation = Transform.GetLocation();

			if (FVector TargetVector = MoveTarget - CurrentLocation; TargetVector.Size()<= 20.f)
			{
				MoveTarget = FVector(FMath::RandRange(-1.f, 1.f) * 1000.f, FMath::RandRange(-1.f, 1.f) * 1000.f, CurrentLocation.Z);
				SimpleMovementsList[EntityIndex].Target =  MoveTarget;
			}
		}
	});
}
