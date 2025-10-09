// // Copyright (c) 2025, Arthur Durand. All rights reserved.


#include "AI/Processors/GAMovementProcessor.h"

#include "MassCommonFragments.h"
#include "MassCommonTypes.h"
#include "MassExecutionContext.h"
#include "MassEntityManager.h"
#include "MassMovementFragments.h"
#include "MassNavigationFragments.h"
#include "AI/Fragments/GAFragments.h"

UGAMovementProcessor::UGAMovementProcessor(): EntityQuery(*this)
{
	bAutoRegisterWithProcessingPhases = true;
	ExecutionFlags = (int32)(EProcessorExecutionFlags::All);
	ExecutionOrder.ExecuteBefore.Add(UE::Mass::ProcessorGroupNames::Avoidance);
}

void UGAMovementProcessor::ConfigureQueries(const TSharedRef<FMassEntityManager>& EntityManager)
{
	EntityQuery.AddRequirement<FTransformFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddRequirement<FMassMoveTargetFragment>(EMassFragmentAccess::ReadWrite);
	EntityQuery.AddConstSharedRequirement<FMassMovementParameters>(EMassFragmentPresence::All);
	EntityQuery.AddRequirement<FGATargetFragment>(EMassFragmentAccess::ReadOnly);
}

void UGAMovementProcessor::Execute(FMassEntityManager& EntityManager, FMassExecutionContext& Context)
{
	EntityQuery.ForEachEntityChunk( Context, [this](FMassExecutionContext& Context)
	{
		const TArrayView<FTransformFragment> TransformsList = Context.GetMutableFragmentView<FTransformFragment>();
		const TArrayView<FMassMoveTargetFragment> NavTargetsList = Context.GetMutableFragmentView<FMassMoveTargetFragment>();
		const TConstArrayView<FGATargetFragment> TargetsList = Context.GetFragmentView<FGATargetFragment>();
		const FMassMovementParameters& MovementParams = Context.GetConstSharedFragment<FMassMovementParameters>();
		
		for (int32 EntityIndex = 0; EntityIndex < Context.GetNumEntities(); ++EntityIndex)
		{
			const FTransform& Transform = TransformsList[EntityIndex].GetTransform();
			FMassMoveTargetFragment& MoveTarget = NavTargetsList[EntityIndex];
			
			const FVector CurrentLocation = Transform.GetLocation();

			// Rotate the entity to face the target
			TransformsList[EntityIndex].SetTransform(FTransform(MoveTarget.Forward.Rotation(), CurrentLocation));
			
			MoveTarget.Center = CurrentLocation;
			FVector TargetVector = TargetsList[EntityIndex].Target - Transform.GetLocation();
			TargetVector.Z = 0.f;
			MoveTarget.DistanceToGoal = TargetVector.Size();
			MoveTarget.Forward = TargetVector.GetSafeNormal();
			MoveTarget.DesiredSpeed =FMassInt16Real(MovementParams.DefaultDesiredSpeed);

			
		}
	});
}
